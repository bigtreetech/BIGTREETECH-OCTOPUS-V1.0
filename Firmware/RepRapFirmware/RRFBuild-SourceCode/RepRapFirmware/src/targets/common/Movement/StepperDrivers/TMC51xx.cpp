/*
 * TMC51xx.cpp
 *
 *  Created on: 26 Aug 2018
 *      Author: David
 *  Purpose:
 *  	Support for TMC5130, TMC5160 and TMC5161 stepper drivers
 */

#include "SmartDrivers.h"

#if SUPPORT_TMC51xx

#include <RTOSIface/RTOSIface.h>
#include <Platform/TaskPriorities.h>
#include <Movement/Move.h>
#include <Hardware/SharedSpi/SharedSpiDevice.h>
#include <Hardware/SharedSpi/SharedSpiClient.h>
#include <Endstops/Endstop.h>
#include <General/Portability.h>
#include "TmcDriverState.h"
#include "TMC51xxDriver.h"


static inline const Move& GetMoveInstance() noexcept { return reprap.GetMove(); }

//#define TMC_TYPE	5130
#define TMC_TYPE	5160
#define DEBUG_DRIVER_TIMEOUT	0

// TMC51xx DRV_STATUS register bit assignments
const uint32_t TMC51xx_RR_SG = 1 << 24;					// stall detected
const uint32_t TMC51xx_RR_OT = 1 << 25;					// over temperature shutdown
const uint32_t TMC51xx_RR_OTPW = 1 << 26;				// over temperature warning
const uint32_t TMC51xx_RR_S2G = (3 << 27) | (3 << 12);	// short to ground indicator (1 bit for each phase) + short to VS indicator
const uint32_t TMC51xx_RR_OLA = 1 << 29;				// open load A
const uint32_t TMC51xx_RR_OLB = 1 << 30;				// open load B
const uint32_t TMC51xx_RR_STST = 1 << 31;				// standstill detected
const uint32_t TMC51xx_RR_SGRESULT = 0x3FF;				// 10-bit stallGuard2 result

constexpr float MinimumMotorCurrent = 50.0;
constexpr float MinimumOpenLoadMotorCurrent = 500;			// minimum current in mA for the open load status to be taken seriously
constexpr uint32_t DefaultMicrosteppingShift = 4;			// x16 microstepping
constexpr bool DefaultInterpolation = true;					// interpolation enabled
constexpr uint32_t DefaultTpwmthrsReg = 2000;				// low values (high changeover speed) give horrible jerk at the changeover from stealthChop to spreadCycle
const int DefaultStallDetectThreshold = 1;
const bool DefaultStallDetectFiltered = false;
const unsigned int DefaultMinimumStepsPerSecond = 200;		// for stall detection: 1 rev per second assuming 1.8deg/step, as per the TMC5160 datasheet
const uint32_t DefaultTcoolthrs = 2000;						// max interval between 1/256 microsteps for stall detection to be enabled
const uint32_t DefaultThigh = 200;
constexpr size_t TmcTaskStackWords = 100;

#if TMC_TYPE == 5130
constexpr float SenseResistor = 0.11;						// 0.082R external + 0.03 internal
#elif TMC_TYPE == 5160
// We now define MaxTmc5160Current in the board configuration file because it varies between boards
constexpr float MaximumStandstillCurrent = MaxTmc5160Current * 0.707;
#if STM32F4
constexpr float SenseResistor = 0.075;						// This seems to be common for most modules
#else
constexpr float SenseResistor = 0.050;						// assume same as we use for TMC2660
#endif
constexpr float RecipFullScaleCurrent = SenseResistor/325.0;		// 1.0 divided by full scale current in mA
#endif

// The SPI clock speed is a compromise:
// - too high and polling the driver chips take too much of the CPU time
// - too low and we won't detect stalls quickly enough
// With a 4MHz SPI clock:
// - polling the drivers makes calculations take ??% longer, so it is taking about ??% of the CPU time
// - we poll all ?? drivers in about ??us
// With a 2MHz SPI clock:
// - polling the drivers makes calculations take ??% longer, so it is taking about ??% of the CPU time
// - we poll all ?? drivers in about ??us
const uint32_t DriversSpiClockFrequency = 2000000;			// 2MHz SPI clock
const uint32_t TransferTimeout = 2;							// any transfer should complete within 2 ticks @ 1ms/tick

// GCONF register (0x00, RW)
constexpr uint8_t REGNUM_GCONF = 0x00;

constexpr uint32_t GCONF_5130_USE_VREF = 1 << 0;			// use external VRef
constexpr uint32_t GCONF_5130_INT_RSENSE = 1 << 1;			// use internal sense resistors
constexpr uint32_t GCONF_5130_END_COMMUTATION = 1 << 3;		// Enable commutation by full step encoder (DCIN_CFG5 = ENC_A, DCEN_CFG4 = ENC_B)

constexpr uint32_t GCONF_5160_RECAL = 1 << 0;				// Zero crossing recalibration during driver disable (via ENN or via TOFF setting)
constexpr uint32_t GCONF_5160_FASTSTANDSTILL = 1 << 1;		// Timeout for step execution until standstill detection: 1: Short time: 2^18 clocks, 0: Normal time: 2^20 clocks
constexpr uint32_t GCONF_5160_MULTISTEP_FILT = 1 << 3;		// Enable step input filtering for stealthChop optimization with external step source (default=1)

constexpr uint32_t GCONF_STEALTHCHOP = 1 << 2;				// use stealthchop mode (else spread cycle mode)
constexpr uint32_t GCONF_REV_DIR = 1 << 4;					// reverse motor direction
constexpr uint32_t GCONF_DIAG0_ERROR = 1 << 5;				// Enable DIAG0 active on driver errors: Over temperature (ot), short to GND (s2g), undervoltage chargepump (uv_cp)
															// DIAG0 always shows the reset-status, i.e. is active low during reset condition.
constexpr uint32_t GCONF_DIAG0_OTPW = 1 << 6;				// Enable DIAG0 active on driver over temperature prewarning (otpw)
constexpr uint32_t GCONF_DIAG0_STALL = 1 << 7;				// Enable DIAG0 active on motor stall (set TCOOLTHRS before using this feature)
constexpr uint32_t GCONF_DIAG1_STALL = 1 << 8;				// Enable DIAG1 active on motor stall (set TCOOLTHRS before using this feature)
constexpr uint32_t GCONF_DIAG1_INDEX = 1 << 9;				// Enable DIAG1 active on index position (microstep look up table position 0)
constexpr uint32_t GCONF_DIAG1_ONSTATE = 1 << 10;			// Enable DIAG1 active when chopper is on (for the coil which is in the second half of the fullstep)
constexpr uint32_t GCONF_DIAG1_STEPS_SKIPPED = 1 << 11;		// Enable output toggle when steps are skipped in dcStep mode (increment of LOST_STEPS). Do not enable in conjunction with other DIAG1 options.
constexpr uint32_t GCONF_DIAG0_PUSHPULL = 1 << 12;			// 0: SWN_DIAG0 is open collector output (active low), 1: Enable SWN_DIAG0 push pull output (active high)
constexpr uint32_t GCONF_DIAG1_PUSHPULL = 1 << 13;			// 0: SWN_DIAG1 is open collector output (active low), 1: Enable SWN_DIAG1 push pull output (active high)
constexpr uint32_t GCONF_SMALL_HYSTERESIS = 1 << 14;		// 0: Hysteresis for step frequency comparison is 1/16, 1: Hysteresis for step frequency comparison is 1/32
constexpr uint32_t GCONF_STOP_ENABLE = 1 << 15;				// 0: Normal operation, 1: Emergency stop: ENCA_DCIN stops the sequencer when tied high (no steps become executed by the sequencer, motor goes to standstill state)
constexpr uint32_t GCONF_DIRECT_MODE = 1 << 16;				// 0: Normal operation, 1: Motor coil currents and polarity directly programmed via serial interface:
															// Register XTARGET (0x2D) specifies signed coil A current (bits 8..0) and coil B current (bits 24..16).
															// In this mode, the current is scaled by IHOLD setting. Velocity based current regulation of stealthChop
															// is not available in this mode. The automatic stealthChop current regulation will work only for low stepper motor velocities.
constexpr uint32_t GCONF_TEST_MODE = 1 << 17;				// 0: Normal operation, 1: Enable analog test output on pin ENCN_DCO. IHOLD[1..0] selects the function of ENCN_DCO: 0…2: T120, DAC, VDDH

#if TMC_TYPE == 5130
constexpr uint32_t DefaultGConfReg = GCONF_DIAG0_STALL | GCONF_DIAG0_PUSHPULL;
#elif TMC_TYPE == 5160
constexpr uint32_t DefaultGConfReg = GCONF_5160_RECAL | GCONF_5160_MULTISTEP_FILT | GCONF_DIAG0_STALL | GCONF_DIAG0_PUSHPULL;
#endif

// General configuration and status registers

// GSTAT register (0x01, RW). Write 1 bits to clear the flags.
constexpr uint8_t REGNUM_GSTAT = 0x01;
constexpr uint32_t GSTAT_RESET = 1 << 0;					// driver has been reset since last read
constexpr uint32_t GSTAT_DRV_ERR = 1 << 1;					// driver has been shut down due to over temp or short circuit
constexpr uint32_t GSTAT_UV_CP = 1 << 2;					// undervoltage on charge pump, driver disabled. Not latched so does not need to be cleared.

// IFCOUNT register (0x02, RO) is not used in SPI mode
// SLAVECONF register (0x03, WO) is not used in SPI mode
// IOIN register (0x04, RO) reads the state of all input pins. We don't use it.
// OUTPUT register (0x04, WO) is not used in SPI mode
// X_COMPARE register (0x05, WO) allows us to get a pulse on DIAG1 when an index is passed. We don't use it.
// OTP_PROG register (0x06, WO, 5160 only) is not used in this firmware
// OTP_READ register (0x07, RO, 5160 only) is not used in this firmware
// FACTORY_CONF register (0x08, RW, 5160 only) trims the clock frequency and is preset for 12MHz

#if TMC_TYPE == 5160

// SHORT_CONF register
constexpr uint8_t REGNUM_5160_SHORTCONF = 0x09;

constexpr uint32_t SHORTCONF_S2VS_LEVEL_SHIFT = 0;
constexpr uint32_t SHORTCONF_S2VS_LEVEL_MASK = 15;			// Short to VS detector level for lowside FETs. Checks for voltage drop in LS MOSFET and sense resistor.
															// 4 (highest sensitivity) … 15 (lowest sensitivity); 10 recommended for normal operation (Reset default 12 via OTP)
															// Hint: Settings from 1 to 3 will trigger during normal operation due to voltage drop on sense resistor.
constexpr uint32_t SHORTCONF_S2G_LEVEL_SHIFT = 8;
constexpr uint32_t SHORTCONF_S2G_LEVEL_MASK = (15 << 8);	// Short to GND detector level for highside FETs. Checks for voltage drop on high side MOSFET
															// 2 (highest sensitivity) … 15 (lowest sensitivity) 6 to 10 recommended (Reset Default: 12 via OTP)
constexpr uint32_t SHORTCONF_FILTER_SHIFT = 16;
constexpr uint32_t SHORTCONF_FILTER_MASK = (3 << 16);		// Spike filtering bandwidth for short detection 0 (lowest, 100ns), 1 (1us), 2 (2us) 3 (3us)
															// Hint: A good PCB layout will allow using setting 0. Increase value, if erroneous short detection occurs. Reset Default = 1
constexpr uint32_t SHORTCONF_DELAY = (1 << 18);				// Short detection delay 0=750ns: normal, 1=1500ns: high The short detection delay shall cover the bridge switching time.
															// 0 will work for most applications. (Reset Default = 0)
constexpr uint32_t DefaultShortConfReg = (10 << SHORTCONF_S2VS_LEVEL_SHIFT) | (6 << SHORTCONF_S2G_LEVEL_SHIFT) | (0 << SHORTCONF_FILTER_SHIFT);

// DRV_CONF register
constexpr uint8_t REGNUM_5160_DRVCONF = 0x0A;
constexpr uint32_t DRVCONF_BBMTIME_SHIFT = 0;
constexpr uint32_t DRVCONF_BBMTIME_MASK = 31;				// Break-Before make delay 0=shortest (100ns) … 16 (200ns) … 24=longest (375ns) >24 not recommended, use BBMCLKS instead
															// Hint: 0 recommended due to fast switching MOSFETs (Reset Default = 0)
constexpr uint32_t DRVCONF_BBMCLKS_SHIFT = 8;
constexpr uint32_t DRVCONF_BBMCLKS_MASK = (15 << 8);		// Digital BBM time in clock cycles (typ. 83ns). The longer setting rules (BBMTIME vs. BBMCLKS).
															// Reset Default: 2 via OTP. Hint: 2, or down to 0 recommended due to fast switching MOSFETs
constexpr uint32_t DRVCONF_OTSELECT_SHIFT = 16;
constexpr uint32_t DRVCONF_OTSELECT_MASK = (3 << 16);		// Selection of over temperature level for bridge disable, switch on after cool down to 120°C / OTPW level. Reset Default = 0.
															// 00: 150°C (not recommended – MOSFET might overheat); 01: 143°C 10: 136°C (Recommended); 11: 120°C (not recommended, no hysteresis)
															// Hint: Adapt overtemperature threshold as required to protect the MOSFETs or other components on the PCB.
constexpr uint32_t DRVCONF_STRENGTH_SHIFT = 18;
constexpr uint32_t DRVCONF_STRENGTH_MASK = (3 << 18);		// Selection of gate driver current. Adapts the gate driver current to the gate charge of the external MOSFETs.
															// 00: Normal slope (Recommended), 01: Normal+TC (medium above OTPW level), 10: Fast slope. Reset Default = 10.
constexpr uint32_t DRVCONF_FILT_ISENSE_SHIFT = 20;
constexpr uint32_t DRVCONF_FILT_ISENSE_MASK = (3 << 20);	// Filter time constant of sense amplifier to suppress ringing and coupling from second coil operation
															// 00: low – 100ns 01: – 200ns 10: – 300ns 11: high – 400ns
															// Hint: Increase setting if motor chopper noise occurs due to cross-coupling of both coils. Reset Default = 0.
constexpr uint32_t DefaultDrvConfReg = (2 << DRVCONF_BBMCLKS_SHIFT) | (2 << DRVCONF_OTSELECT_SHIFT);

constexpr uint8_t REGNUM_5160_GLOBAL_SCALER = 0x0B;			// Global scaling of Motor current. This value is multiplied to the current scaling in order to adapt a drive to a
															// certain motor type. This value should be chosen before tuning other settings, because it also influences chopper hysteresis.
															// 0: Full Scale (or write 256) 1 … 31: Not allowed for operation 32 … 255: 32/256 … 255/256 of maximum current.
															// Hint: Values >128 recommended for best results. Reset Default 0.
constexpr uint32_t DefaultGlobalScalerReg = 0;				// until we use it as part of the current setting

constexpr uint8_t REGNUM_5160_OFFSET_READ = 0x0B;			// Bits 8..15: Offset calibration result phase A (signed). Bits 0..7: Offset calibration result phase B (signed).

#endif

// Velocity dependent control registers

// IHOLD_IRUN register (WO)
constexpr uint8_t REGNUM_IHOLDIRUN = 0x10;
constexpr uint32_t IHOLDIRUN_IHOLD_SHIFT = 0;				// standstill current
constexpr uint32_t IHOLDIRUN_IHOLD_MASK = 0x1F << IHOLDIRUN_IHOLD_SHIFT;
constexpr uint32_t IHOLDIRUN_IRUN_SHIFT = 8;
constexpr uint32_t IHOLDIRUN_IRUN_MASK = 0x1F << IHOLDIRUN_IRUN_SHIFT;
constexpr uint32_t IHOLDIRUN_IHOLDDELAY_SHIFT = 16;
constexpr uint32_t IHOLDIRUN_IHOLDDELAY_MASK = 0x0F << IHOLDIRUN_IHOLDDELAY_SHIFT;

constexpr uint32_t DefaultIholdIrunReg = (0 << IHOLDIRUN_IHOLD_SHIFT) | (0 << IHOLDIRUN_IRUN_SHIFT) | (2 << IHOLDIRUN_IHOLDDELAY_SHIFT);
															// approx. 0.5 sec motor current reduction to half power

constexpr uint8_t REGNUM_TPOWER_DOWN = 0x11;
constexpr uint8_t REGNUM_TSTEP = 0x12;
constexpr uint8_t REGNUM_TPWMTHRS = 0x13;

constexpr uint8_t REGNUM_TCOOLTHRS = 0x14;
const uint32_t DefaultTcoolthrsReg = DefaultTcoolthrs;

constexpr uint8_t REGNUM_THIGH = 0x15;
const uint32_t DefaultThighReg = DefaultThigh;

constexpr uint8_t REGNUM_VACTUAL = 0x22;

// Sequencer registers (read only)
constexpr uint8_t REGNUM_MSCNT = 0x6A;
constexpr uint8_t REGNUM_MSCURACT = 0x6B;

// Chopper control registers

// CHOPCONF register
constexpr uint8_t REGNUM_CHOPCONF = 0x6C;
constexpr uint32_t CHOPCONF_TOFF_SHIFT = 0;					// off time setting, 0 = disable driver
constexpr uint32_t CHOPCONF_TOFF_MASK = 0x0F << CHOPCONF_TOFF_SHIFT;
constexpr uint32_t CHOPCONF_HSTRT_SHIFT = 4;				// hysteresis start
constexpr uint32_t CHOPCONF_HSTRT_MASK = 0x07 << CHOPCONF_HSTRT_SHIFT;
constexpr uint32_t CHOPCONF_HEND_SHIFT = 7;					// hysteresis end
constexpr uint32_t CHOPCONF_HEND_MASK = 0x0F << CHOPCONF_HEND_SHIFT;
constexpr uint32_t CHOPCONF_5130_RNDTOFF = 1 << 13;			// random off time
constexpr uint32_t CHOPCONF_CHM = 1 << 14;					// fixed off time
constexpr uint32_t CHOPCONF_TBL_SHIFT = 15;					// blanking time
constexpr uint32_t CHOPCONF_TBL_MASK = 0x03 << CHOPCONF_TBL_SHIFT;
constexpr uint32_t CHOPCONF_5130_VSENSE_HIGH = 1 << 17;		// use high sensitivity current scaling
constexpr uint32_t CHOPCONF_MRES_SHIFT = 24;				// microstep resolution
constexpr uint32_t CHOPCONF_MRES_MASK = 0x0F << CHOPCONF_MRES_SHIFT;
constexpr uint32_t CHOPCONF_INTPOL = 1 << 28;				// use interpolation
constexpr uint32_t CHOPCONF_DEDGE = 1 << 29;				// step on both edges
constexpr uint32_t CHOPCONF_DISS2G = 1 << 30;				// disable short to ground protection
constexpr uint32_t CHOPCONF_DISS2VS = 1 << 31;				// disable low side short protection

#if TMC_TYPE == 5130
constexpr uint32_t DefaultChopConfReg = (1 << CHOPCONF_TBL_SHIFT) | (3 << CHOPCONF_TOFF_SHIFT) | (5 << CHOPCONF_HSTRT_SHIFT) | CHOPCONF_5130_VSENSE_HIGH;
#elif TMC_TYPE == 5160
constexpr uint32_t DefaultChopConfReg = (1 << CHOPCONF_TBL_SHIFT) | (3 << CHOPCONF_TOFF_SHIFT) | (5 << CHOPCONF_HSTRT_SHIFT);
#endif

constexpr uint8_t REGNUM_COOLCONF = 0x6D;
constexpr uint32_t COOLCONF_SGFILT = 1 << 24;				// set to update stallGuard status every 4 full steps instead of every full step
constexpr uint32_t COOLCONF_SGT_SHIFT = 16;
constexpr uint32_t COOLCONF_SGT_MASK = 127 << COOLCONF_SGT_SHIFT;	// stallguard threshold (signed)

constexpr uint32_t DefaultCoolConfReg = 0;

// DRV_STATUS register. See the .h file for the bit definitions.
constexpr uint8_t REGNUM_DRV_STATUS = 0x6F;

// PWMCONF register
constexpr uint8_t REGNUM_PWMCONF = 0x70;

constexpr uint32_t DefaultPwmConfReg = 0xC40C001E;			// this is the reset default - try it until we find something better

constexpr uint8_t REGNUM_PWM_SCALE = 0x71;
constexpr uint8_t REGNUM_PWM_AUTO = 0x72;

// Common data
static size_t numTmc51xxDrivers = 0;

enum class DriversState : uint8_t
{
	shutDown = 0,
	noPower,				// no VIN power
	powerWait,
	noDrivers,
	notInitialised,			// have VIN power but not started initialising drivers
	initialising,			// in the process of initialising the drivers
	ready					// drivers are initialised and ready
};

static DriversState driversState = DriversState::shutDown;

//----------------------------------------------------------------------------------------------------------------------------------
// Private types and methods

class Tmc51xxDriverState : public TmcDriverState
{
public:
	Tmc51xxDriverState() noexcept;
	void Init(uint32_t p_driverNumber) noexcept;
	void SetAxisNumber(size_t p_axisNumber) noexcept;
	uint32_t GetAxisNumber() const noexcept { return axisNumber; }
	void WriteAll() noexcept;
	bool SetMicrostepping(uint32_t shift, bool interpolate) noexcept;
	unsigned int GetMicrostepping(bool& interpolation) const noexcept;
	bool SetDriverMode(unsigned int mode) noexcept;
	DriverMode GetDriverMode() const noexcept;
	void SetCurrent(float current) noexcept;
	void Enable(bool en) noexcept;
	void AppendDriverStatus(const StringRef& reply) noexcept;
	bool UpdatePending() const noexcept { return (registersToUpdate | newRegistersToUpdate) != 0; }
#if HAS_STALL_DETECT
	void SetStallDetectThreshold(int sgThreshold) noexcept;
	void SetStallDetectFilter(bool sgFilter) noexcept;
	void SetStallMinimumStepsPerSecond(unsigned int stepsPerSecond) noexcept;
	void AppendStallConfig(const StringRef& reply) const noexcept;
#endif

	bool SetRegister(SmartDriverRegister reg, uint32_t regVal) noexcept;
	uint32_t GetRegister(SmartDriverRegister reg) const noexcept;

	float GetStandstillCurrentPercent() const noexcept;
	void SetStandstillCurrentPercent(float percent) noexcept;

	uint32_t ReadLiveStatus() const noexcept;
	uint32_t ReadAccumulatedStatus(uint32_t bitsToKeep) noexcept;

	void GetSpiCommand(uint8_t *sendDdataBlock) noexcept;
	void TransferSucceeded(const uint8_t *rcvDataBlock) noexcept;
	void TransferFailed() noexcept;
	DriversState SetupDriver(bool reset) noexcept;
	bool inline IsReady() noexcept {return ready;}
	uint8_t inline GetDriverNumber() const noexcept { return driverNumber; }

private:
	bool ready;
	uint8_t driverNumber;
	bool SetChopConf(uint32_t newVal) noexcept;
	void UpdateRegister(size_t regIndex, uint32_t regVal) noexcept;
	void UpdateChopConfRegister() noexcept;							// calculate the chopper control register and flag it for sending
	void UpdateCurrent() noexcept;

	void ResetLoadRegisters() noexcept
	{
		minSgLoadRegister = 1023;
		maxSgLoadRegister = 0;
	}

	// Write register numbers are in priority order, most urgent first, in same order as WriteRegNumbers
	static constexpr unsigned int WriteGConf = 0;			// microstepping
	static constexpr unsigned int WriteIholdIrun = 1;		// current setting
	static constexpr unsigned int WriteTpwmthrs = 2;		// upper step rate limit for stealthchop
	static constexpr unsigned int WriteTcoolthrs = 3;		// lower velocity for coolStep and stallGuard
	static constexpr unsigned int WriteThigh = 4;			// upper velocity for coolStep and stealthChop
	static constexpr unsigned int WriteChopConf = 5;		// chopper control
	static constexpr unsigned int WriteCoolConf = 6;		// coolstep control
	static constexpr unsigned int WritePwmConf = 7;			// stealthchop and freewheel control
#if TMC_TYPE == 5160
	static constexpr unsigned int Write5160ShortConf = 8;	// short circuit detection configuration
	static constexpr unsigned int Write5160DrvConf = 9;		// driver timing
	static constexpr unsigned int Write5160GlobalScaler = 10; // motor current scaling

	static constexpr unsigned int NumWriteRegisters = 11;	// the number of registers that we write to
#else
	static constexpr unsigned int NumWriteRegisters = 8;	// the number of registers that we write to
#endif

	static const uint8_t WriteRegNumbers[NumWriteRegisters];	// the register numbers that we write to

	static constexpr unsigned int NumReadRegisters = 5;		// the number of registers that we read from
	static const uint8_t ReadRegNumbers[NumReadRegisters];	// the register numbers that we read from

	// Read register numbers, in same order as ReadRegNumbers
	static constexpr unsigned int ReadGStat = 0;
	static constexpr unsigned int ReadDrvStat = 1;
	static constexpr unsigned int ReadMsCnt = 2;
	static constexpr unsigned int ReadPwmScale = 3;
	static constexpr unsigned int ReadPwmAuto = 4;

	static constexpr uint8_t NoRegIndex = 0xFF;				// this means no register updated, or no register requested

	volatile uint32_t writeRegisters[NumWriteRegisters];	// the values we want the TMC22xx writable registers to have
	volatile uint32_t readRegisters[NumReadRegisters];		// the last values read from the TMC22xx readable registers
	volatile uint32_t accumulatedDriveStatus;				// the accumulated drive status bits

	uint32_t configuredChopConfReg;							// the configured chopper control register, in the Enabled state, without the microstepping bits
	uint32_t maxStallStepInterval;							// maximum interval between full steps to take any notice of stall detection
	uint32_t minSgLoadRegister;								// the minimum value of the StallGuard bits we read
	uint32_t maxSgLoadRegister;								// the maximum value of the StallGuard bits we read

	volatile uint32_t newRegistersToUpdate;					// bitmap of register indices whose values need to be sent to the driver chip
	uint32_t registersToUpdate;								// bitmap of register indices whose values need to be sent to the driver chip
	DriversBitmap driverBit;								// bitmap of just this driver number
	uint32_t axisNumber;									// the axis number of this driver as used to index the DriveMovements in the DDA
	uint32_t microstepShiftFactor;							// how much we need to shift 1 left by to get the current microstepping
	uint32_t motorCurrent;									// the configured motor current in mA

	uint16_t numReads, numWrites;							// how many successful reads and writes we had

	uint8_t standstillCurrentFraction;						// divide this by 256 to get the motor current standstill fraction
	uint8_t regIndexBeingUpdated;							// which register we are sending
	uint8_t regIndexRequested;								// the register we asked to read in the previous transaction, or 0xFF
	uint8_t previousRegIndexRequested;						// the register we asked to read in the previous transaction, or 0xFF
	bool enabled;											// true if driver is enabled
};

const uint8_t Tmc51xxDriverState::WriteRegNumbers[NumWriteRegisters] =
{
	REGNUM_GCONF,
	REGNUM_IHOLDIRUN,
	REGNUM_TPWMTHRS,
	REGNUM_TCOOLTHRS,
	REGNUM_THIGH,
	REGNUM_CHOPCONF,
	REGNUM_COOLCONF,
	REGNUM_PWMCONF,
#if TMC_TYPE == 5160
	REGNUM_5160_SHORTCONF,
	REGNUM_5160_DRVCONF,
	REGNUM_5160_GLOBAL_SCALER
#endif
};

const uint8_t Tmc51xxDriverState::ReadRegNumbers[NumReadRegisters] =
{
	REGNUM_GSTAT,
	REGNUM_DRV_STATUS,
	REGNUM_MSCNT,
	REGNUM_PWM_SCALE,
	REGNUM_PWM_AUTO
};

Tmc51xxDriverState::Tmc51xxDriverState() noexcept : TmcDriverState(), accumulatedDriveStatus(0), configuredChopConfReg(0), maxStallStepInterval(0),
	minSgLoadRegister(0), maxSgLoadRegister(0), newRegistersToUpdate(0), registersToUpdate(0), axisNumber(0), microstepShiftFactor(0),
	motorCurrent(0), enabled(0)
{
}

// Initialise the state of the driver and its CS pin
void Tmc51xxDriverState::Init(uint32_t p_driverNumber) noexcept
pre(!driversPowered)
{
	driverNumber = p_driverNumber;
	ready = false;
	axisNumber = p_driverNumber;										// axes are mapped straight through to drivers initially
	driverBit = DriversBitmap::MakeFromBits(p_driverNumber);
	enabled = false;
	registersToUpdate = newRegistersToUpdate = 0;
	motorCurrent = 0;
	standstillCurrentFraction = (uint8_t)min<uint32_t>((DefaultStandstillCurrentPercent * 256)/100, 255);

	// Set default values for all registers and flag them to be updated
	UpdateRegister(WriteGConf, DefaultGConfReg);
#if TMC_TYPE == 5160
	UpdateRegister(Write5160ShortConf, DefaultShortConfReg);
	UpdateRegister(Write5160DrvConf, DefaultDrvConfReg);
	UpdateRegister(Write5160GlobalScaler, DefaultGlobalScalerReg);
#endif
	UpdateRegister(WriteIholdIrun, DefaultIholdIrunReg);
	UpdateRegister(WriteTpwmthrs, DefaultTpwmthrsReg);
	UpdateRegister(WriteTcoolthrs, DefaultTcoolthrsReg);
	UpdateRegister(WriteThigh, DefaultThighReg);
	configuredChopConfReg = DefaultChopConfReg;
	SetMicrostepping(DefaultMicrosteppingShift, DefaultInterpolation);	// this also updates the chopper control register
	writeRegisters[WriteCoolConf] = DefaultCoolConfReg;
#if HAS_STALL_DETECT
	SetStallDetectThreshold(DefaultStallDetectThreshold);				// this also updates the CoolConf register
	SetStallMinimumStepsPerSecond(DefaultMinimumStepsPerSecond);
#endif
	UpdateRegister(WritePwmConf, DefaultPwmConfReg);

	for (size_t i = 0; i < NumReadRegisters; ++i)
	{
		readRegisters[i] = 0;
	}
	accumulatedDriveStatus = 0;

	regIndexBeingUpdated = regIndexRequested = previousRegIndexRequested = NoRegIndex;
	numReads = numWrites = 0;
	ResetLoadRegisters();
}

// Set a register value and flag it for updating
void Tmc51xxDriverState::UpdateRegister(size_t regIndex, uint32_t regVal) noexcept
{
	writeRegisters[regIndex] = regVal;
	newRegistersToUpdate |= (1u << regIndex);							// flag it for sending
}

// Calculate the chopper control register and flag it for sending
void Tmc51xxDriverState::UpdateChopConfRegister() noexcept
{
	UpdateRegister(WriteChopConf, (enabled) ? configuredChopConfReg : configuredChopConfReg & ~CHOPCONF_TOFF_MASK);
}

inline void Tmc51xxDriverState::SetAxisNumber(size_t p_axisNumber) noexcept
{
	axisNumber = p_axisNumber;
}

// Write all registers. This is called when the drivers are known to be powered up.
inline void Tmc51xxDriverState::WriteAll() noexcept
{
	newRegistersToUpdate = (1u << NumWriteRegisters) - 1;
}

float Tmc51xxDriverState::GetStandstillCurrentPercent() const noexcept
{
	return (float)(standstillCurrentFraction * 100)/256;
}

void Tmc51xxDriverState::SetStandstillCurrentPercent(float percent) noexcept
{
	standstillCurrentFraction = (uint8_t)constrain<long>(lrintf((percent * 256)/100), 0, 255);
	UpdateCurrent();
}

// Set the microstepping and microstep interpolation. The desired microstepping is (1 << shift).
bool Tmc51xxDriverState::SetMicrostepping(uint32_t shift, bool interpolate) noexcept
{
	microstepShiftFactor = shift;
	configuredChopConfReg = (configuredChopConfReg & ~(CHOPCONF_MRES_MASK | CHOPCONF_INTPOL)) | ((8 - shift) << CHOPCONF_MRES_SHIFT);
	if (interpolate)
	{
		configuredChopConfReg |= CHOPCONF_INTPOL;
	}
	UpdateChopConfRegister();
	return true;
}

// Get microstepping or chopper control register
unsigned int Tmc51xxDriverState::GetMicrostepping(bool& interpolation) const noexcept
{
	interpolation = (writeRegisters[WriteChopConf] & CHOPCONF_INTPOL) != 0;
	return 1u << microstepShiftFactor;
}

bool Tmc51xxDriverState::SetRegister(SmartDriverRegister reg, uint32_t regVal) noexcept
{
	switch (reg)
	{
	case SmartDriverRegister::chopperControl:
		return SetChopConf(regVal);

	case SmartDriverRegister::toff:
		return SetChopConf((configuredChopConfReg & ~CHOPCONF_TOFF_MASK) | ((regVal << CHOPCONF_TOFF_SHIFT) & CHOPCONF_TOFF_MASK));

	case SmartDriverRegister::tblank:
		return SetChopConf((configuredChopConfReg & ~CHOPCONF_TBL_MASK) | ((regVal << CHOPCONF_TBL_SHIFT) & CHOPCONF_TBL_MASK));

	case SmartDriverRegister::hstart:
		return SetChopConf((configuredChopConfReg & ~CHOPCONF_HSTRT_MASK) | ((regVal << CHOPCONF_HSTRT_SHIFT) & CHOPCONF_HSTRT_MASK));

	case SmartDriverRegister::hend:
		return SetChopConf((configuredChopConfReg & ~CHOPCONF_HEND_MASK) | ((regVal << CHOPCONF_HEND_SHIFT) & CHOPCONF_HEND_MASK));

	case SmartDriverRegister::tpwmthrs:
		UpdateRegister(WriteTpwmthrs, regVal & ((1u << 20) - 1));
		return true;

	case SmartDriverRegister::thigh:
		UpdateRegister(WriteThigh, regVal & ((1u << 20) - 1));
		return true;

	case SmartDriverRegister::coolStep:
		UpdateRegister(WriteTcoolthrs, regVal & ((1u << 20) - 1));
		return true;

	case SmartDriverRegister::hdec:
	default:
		return false;
	}
}

uint32_t Tmc51xxDriverState::GetRegister(SmartDriverRegister reg) const noexcept
{
	switch(reg)
	{
	case SmartDriverRegister::chopperControl:
		return configuredChopConfReg & 0x01FFFF;

	case SmartDriverRegister::toff:
		return (configuredChopConfReg & CHOPCONF_TOFF_MASK) >> CHOPCONF_TOFF_SHIFT;

	case SmartDriverRegister::tblank:
		return (configuredChopConfReg & CHOPCONF_TBL_MASK) >> CHOPCONF_TBL_SHIFT;

	case SmartDriverRegister::hstart:
		return (configuredChopConfReg & CHOPCONF_HSTRT_MASK) >> CHOPCONF_HSTRT_SHIFT;

	case SmartDriverRegister::hend:
		return (configuredChopConfReg & CHOPCONF_HEND_MASK) >> CHOPCONF_HEND_SHIFT;

	case SmartDriverRegister::tpwmthrs:
		return writeRegisters[WriteTpwmthrs];

	case SmartDriverRegister::thigh:
		return writeRegisters[WriteThigh];

	case SmartDriverRegister::coolStep:
		return writeRegisters[WriteTcoolthrs];

	case SmartDriverRegister::mstepPos:
		return readRegisters[ReadMsCnt];

	case SmartDriverRegister::pwmScale:
		return readRegisters[ReadPwmScale];

	case SmartDriverRegister::pwmAuto:
		return readRegisters[ReadPwmAuto];

	case SmartDriverRegister::hdec:
	default:
		return 0;
	}
}

// Set the chopper control register to the settings provided by the user. We allow only the lowest 17 bits to be set.
bool Tmc51xxDriverState::SetChopConf(uint32_t newVal) noexcept
{
	const uint32_t offTime = (newVal & CHOPCONF_TOFF_MASK) >> CHOPCONF_TOFF_SHIFT;
	if (offTime == 0 || (offTime == 1 && (newVal & CHOPCONF_TBL_MASK) < (2 << CHOPCONF_TBL_SHIFT)))
	{
		return false;
	}
	const uint32_t hstrt = (newVal & CHOPCONF_HSTRT_MASK) >> CHOPCONF_HSTRT_SHIFT;
	const uint32_t hend = (newVal & CHOPCONF_HEND_MASK) >> CHOPCONF_HEND_SHIFT;
	if (hstrt + hend > 16)
	{
		return false;
	}
	const uint32_t userMask = CHOPCONF_TBL_MASK | CHOPCONF_HSTRT_MASK | CHOPCONF_HEND_MASK | CHOPCONF_TOFF_MASK;	// mask of bits the user is allowed to change
	configuredChopConfReg = (configuredChopConfReg & ~userMask) | (newVal & userMask);
	UpdateChopConfRegister();
	return true;
}

// Set the driver mode
bool Tmc51xxDriverState::SetDriverMode(unsigned int mode) noexcept
{
	switch (mode)
	{
	case (unsigned int)DriverMode::spreadCycle:
		UpdateRegister(WriteGConf, writeRegisters[WriteGConf] & ~GCONF_STEALTHCHOP);
		return true;

	case (unsigned int)DriverMode::stealthChop:
		UpdateRegister(WriteGConf, writeRegisters[WriteGConf] | GCONF_STEALTHCHOP);
		return true;

	case (unsigned int)DriverMode::constantOffTime:
		UpdateRegister(WriteGConf, writeRegisters[WriteGConf] & ~GCONF_STEALTHCHOP);
		UpdateRegister(WriteChopConf,
#if TMC_TYPE == 5130
			(writeRegisters[WriteChopConf] | CHOPCONF_CHM) & ~CHOPCONF_5130_RNDTOFF
#else
			writeRegisters[WriteChopConf] | CHOPCONF_CHM
#endif
			);
		return true;

#if TMC_TYPE == 5130
	case (unsigned int)DriverMode::randomOffTime:
		UpdateRegister(WriteGConf, writeRegisters[WriteGConf] & ~GCONF_STEALTHCHOP);
		UpdateRegister(WriteChopConf, writeRegisters[WriteChopConf] | CHOPCONF_CHM | CHOPCONF_5130_RNDTOFF);
		return true;
#endif

	default:
		return false;
	}
}

// Get the driver mode
DriverMode Tmc51xxDriverState::GetDriverMode() const noexcept
{
	return ((writeRegisters[WriteGConf] & GCONF_STEALTHCHOP) != 0) ? DriverMode::stealthChop
		: ((writeRegisters[WriteChopConf] & CHOPCONF_CHM) == 0) ? DriverMode::spreadCycle
#if TMC_TYPE == 5130
			: ((writeRegisters[WriteChopConf] & CHOPCONF_5130_RNDTOFF) != 0) ? DriverMode::randomOffTime
#endif
				: DriverMode::constantOffTime;
}

// Set the motor current
void Tmc51xxDriverState::SetCurrent(float current) noexcept
{
	motorCurrent = static_cast<uint32_t>(constrain<float>(current, MinimumMotorCurrent, MaxTmc5160Current));
	UpdateCurrent();
}

void Tmc51xxDriverState::UpdateCurrent() noexcept
{
#if TMC_TYPE == 5130
	// Assume a current sense resistor of 0.082 ohms, to which we must add 0.025 ohms internal resistance.
	// Full scale peak motor current in the high sensitivity range is give by I = 0.18/(R+0.03) = 0.18/0.105 ~= 1.6A
	// This gives us a range of 50mA to 1.6A in 50mA steps in the high sensitivity range (VSENSE = 1)
	const uint32_t iRunCsBits = (32 * motorCurrent - 800)/1615;		// formula checked by simulation on a spreadsheet
	const uint32_t iHoldCurrent = (motorCurrent * standstillCurrentFraction)/256;	// set standstill current
	const uint32_t iHoldCsBits = (32 * iHoldCurrent - 800)/1615;	// formula checked by simulation on a spreadsheet
	UpdateRegister(WriteIholdIrun,
					(writeRegisters[WriteIholdIrun] & ~(IHOLDIRUN_IRUN_MASK | IHOLDIRUN_IHOLD_MASK)) | (iRunCsBits << IHOLDIRUN_IRUN_SHIFT) | (iHoldCsBits << IHOLDIRUN_IHOLD_SHIFT));
#elif TMC_TYPE == 5160
	// See if we can set IRUN to 31 and do the current adjustment in the global scaler
	uint32_t gs = lrintf(motorCurrent * 256 * RecipFullScaleCurrent);
	uint32_t iRun = 31;
	if (gs >= 256)
	{
		gs = 0;
	}
	else if (gs < 32)
	{
		// We can't regulate the current just through the global scaler because it has a minimum value of 32
		iRun = (gs == 0) ? gs : gs - 1;
		gs = 32;
	}

	// At high motor currents, limit the standstill current fraction to avoid overheating particular pairs of mosfets
	constexpr uint32_t MaxStandstillCurrentTimes256 = 256 * (uint32_t)MaximumStandstillCurrent;
	const uint8_t limitedStandstillCurrentFraction = (motorCurrent * standstillCurrentFraction <= MaxStandstillCurrentTimes256)
														? standstillCurrentFraction
															: (uint8_t)(MaxStandstillCurrentTimes256/motorCurrent);
	const uint32_t iHold = (iRun * limitedStandstillCurrentFraction)/256;
	UpdateRegister(WriteIholdIrun,
					(writeRegisters[WriteIholdIrun] & ~(IHOLDIRUN_IRUN_MASK | IHOLDIRUN_IHOLD_MASK)) | (iRun << IHOLDIRUN_IRUN_SHIFT) | (iHold << IHOLDIRUN_IHOLD_SHIFT));
	UpdateRegister(Write5160GlobalScaler, gs);
#else
# error unknown device
#endif
}

// Enable or disable the driver
void Tmc51xxDriverState::Enable(bool en) noexcept
{
	if (enabled != en)
	{
		enabled = en;
		UpdateChopConfRegister();
	}
}

// Read the status
uint32_t Tmc51xxDriverState::ReadLiveStatus() const noexcept
{
	return readRegisters[ReadDrvStat] & (TMC51xx_RR_SG | TMC51xx_RR_OT | TMC51xx_RR_OTPW | TMC51xx_RR_S2G | TMC51xx_RR_OLA | TMC51xx_RR_OLB | TMC51xx_RR_STST);
}

// Read the status
uint32_t Tmc51xxDriverState::ReadAccumulatedStatus(uint32_t bitsToKeep) noexcept
{
	TaskCriticalSectionLocker lock;
	const uint32_t status = accumulatedDriveStatus;
	accumulatedDriveStatus = (status & bitsToKeep) | readRegisters[ReadDrvStat];		// so that the next call to ReadAccumulatedStatus isn't missing some bits
	// Map 51xx status to 22xx status
	uint32_t ret = 0;
	if (status & TMC51xx_RR_SG) ret |= TMC_RR_SG;
	if (status & TMC51xx_RR_OT) ret |= TMC_RR_OT;
	if (status & TMC51xx_RR_OTPW) ret |= TMC_RR_OTPW;
	if (status & TMC51xx_RR_S2G) ret |= TMC_RR_S2G;
	if (status & TMC51xx_RR_OLA) ret |= TMC_RR_OLA;
	if (status & TMC51xx_RR_OLB) ret |= TMC_RR_OLB;
	if (status & TMC51xx_RR_STST) ret |= TMC_RR_STST;
	return ret;
}

// Append the driver status to a string, and reset the min/max load values
void Tmc51xxDriverState::AppendDriverStatus(const StringRef& reply) noexcept
{
	if (!ready)
	{
		reply.cat("no-driver-detected");
		return;
	}
	reply.catf("5160 ");
	const uint32_t lastReadStatus = readRegisters[ReadDrvStat];
	if (lastReadStatus & TMC51xx_RR_OT)
	{
		reply.cat("temperature-shutdown! ");
	}
	else if (lastReadStatus & TMC51xx_RR_OTPW)
	{
		reply.cat("temperature-warning, ");
	}
	if (lastReadStatus & TMC51xx_RR_S2G)
	{
		reply.cat("short-to-ground, ");
	}
	if ((lastReadStatus & TMC51xx_RR_OLA) && !(lastReadStatus & TMC51xx_RR_STST))
	{
		reply.cat("open-load-A, ");
	}
	if ((lastReadStatus & TMC51xx_RR_OLB) && !(lastReadStatus & TMC51xx_RR_STST))
	{
		reply.cat("open-load-B, ");
	}
	if (lastReadStatus & TMC51xx_RR_STST)
	{
		reply.cat("standstill, ");
	}
	else if ((lastReadStatus & (TMC51xx_RR_OT | TMC51xx_RR_OTPW | TMC51xx_RR_S2G | TMC51xx_RR_OLA | TMC51xx_RR_OLB)) == 0)
	{
		reply.cat("ok, ");
	}

	reply.catf("reads %u, writes %u, ", numReads, numWrites);
	numReads = numWrites = 0;

	if (minSgLoadRegister <= maxSgLoadRegister)
	{
		reply.catf("SG min/max %" PRIu32 "/%" PRIu32, minSgLoadRegister, maxSgLoadRegister);
	}
	else
	{
		reply.cat("SG min/max not available");
	}
	ResetLoadRegisters();
}

#if HAS_STALL_DETECT
void Tmc51xxDriverState::SetStallDetectThreshold(int sgThreshold) noexcept
{
	const uint32_t sgVal = ((uint32_t)constrain<int>(sgThreshold, -64, 63)) & 127u;
	writeRegisters[WriteCoolConf] = (writeRegisters[WriteCoolConf] & ~COOLCONF_SGT_MASK) | (sgVal << COOLCONF_SGT_SHIFT);
	newRegistersToUpdate |= 1u << WriteCoolConf;
}

void Tmc51xxDriverState::SetStallDetectFilter(bool sgFilter) noexcept
{
	if (sgFilter)
	{
		writeRegisters[WriteCoolConf] |= COOLCONF_SGFILT;
	}
	else
	{
		writeRegisters[WriteCoolConf] &= ~COOLCONF_SGFILT;
	}
	newRegistersToUpdate |= 1u << WriteCoolConf;
}

void Tmc51xxDriverState::SetStallMinimumStepsPerSecond(unsigned int stepsPerSecond) noexcept
{
	//TODO use hardware facility instead
	maxStallStepInterval = StepTimer::StepClockRate/max<unsigned int>(stepsPerSecond, 1);
}

void Tmc51xxDriverState::AppendStallConfig(const StringRef& reply) const noexcept
{
	const bool filtered = ((writeRegisters[WriteCoolConf] & COOLCONF_SGFILT) != 0);
	int threshold = (int)((writeRegisters[WriteCoolConf] & COOLCONF_SGT_MASK) >> COOLCONF_SGT_SHIFT);
	if (threshold >= 64)
	{
		threshold -= 128;
	}
	const uint32_t fullstepsPerSecond = StepTimer::StepClockRate/maxStallStepInterval;
	const float speed1 = ((fullstepsPerSecond << microstepShiftFactor)/reprap.GetPlatform().DriveStepsPerUnit(axisNumber));
	const uint32_t tcoolthrs = writeRegisters[WriteTcoolthrs] & ((1ul << 20) - 1u);
	bool bdummy;
	const float speed2 = (12000000.0 * GetMicrostepping(bdummy))/(256 * tcoolthrs * reprap.GetPlatform().DriveStepsPerUnit(axisNumber));
	reply.catf("stall threshold %d, filter %s, steps/sec %" PRIu32 " (%.1f mm/sec), coolstep threshold %" PRIu32 " (%.1f mm/sec)",
				threshold, ((filtered) ? "on" : "off"), fullstepsPerSecond, (double)speed1, tcoolthrs, (double)speed2);
}
#endif

// In the following, only byte accesses to sendDataBlock are allowed, because accesses to non-cacheable memory must be aligned
void Tmc51xxDriverState::GetSpiCommand(uint8_t *sendDataBlock) noexcept
{
	// Find which register to send. The common case is when no registers need to be updated.
	{
		TaskCriticalSectionLocker lock;
		registersToUpdate |= newRegistersToUpdate;
		newRegistersToUpdate = 0;
	}

	if (registersToUpdate == 0)
	{
		// Read a register
		regIndexBeingUpdated = NoRegIndex;
		regIndexRequested = (regIndexRequested >= NumReadRegisters - 1) ? 0 : regIndexRequested + 1;
		sendDataBlock[0] = ReadRegNumbers[regIndexRequested];
		sendDataBlock[1] = 0;
		sendDataBlock[2] = 0;
		sendDataBlock[3] = 0;
		sendDataBlock[4] = 0;
	}
	else
	{
		// Write a register
		const size_t regNum = LowestSetBit(registersToUpdate);
		regIndexBeingUpdated = regNum;
		sendDataBlock[0] = WriteRegNumbers[regNum] | 0x80;
		StoreBE32(sendDataBlock + 1, writeRegisters[regNum]);
	}
}

void Tmc51xxDriverState::TransferSucceeded(const uint8_t *rcvDataBlock) noexcept
{
	// If we wrote a register, mark it up to date
	if (regIndexBeingUpdated < NumWriteRegisters)
	{
		registersToUpdate &= ~(1u << regIndexBeingUpdated);
		++numWrites;
	}

	// Get the full step interval, we will need it later
	const uint32_t interval = GetMoveInstance().GetStepInterval(axisNumber, microstepShiftFactor);		// get the full step interval

	// If we read a register, update our copy
	if (previousRegIndexRequested < NumReadRegisters)
	{
		++numReads;
		uint32_t regVal = LoadBE32(rcvDataBlock + 1);
		if (previousRegIndexRequested == ReadDrvStat)
		{
			// We treat the DRV_STATUS register separately
			if ((regVal & TMC51xx_RR_STST) == 0)							// in standstill, SG_RESULT returns the chopper on-time instead
			{
				const uint32_t sgResult = regVal & TMC51xx_RR_SGRESULT;
				if (sgResult < minSgLoadRegister)
				{
					minSgLoadRegister = sgResult;
				}
				if (sgResult > maxSgLoadRegister)
				{
					maxSgLoadRegister = sgResult;
				}
			}

			if ((regVal & (TMC51xx_RR_OLA | TMC51xx_RR_OLB)) != 0)
			{
				if (   (regVal & TMC51xx_RR_STST) != 0
					|| interval == 0
					|| interval > StepTimer::StepClockRate/MinimumOpenLoadFullStepsPerSec
					|| motorCurrent < MinimumOpenLoadMotorCurrent
				   )
				{
					regVal &= ~(TMC51xx_RR_OLA | TMC51xx_RR_OLB);				// open load bits are unreliable at standstill, low speeds, and low current
				}
			}

			// Only add bits to the accumulator if they appear in 2 successive samples. This is to avoid seeing transient S2G, S2VS, STST and open load errors.
			const uint32_t oldDrvStat = readRegisters[ReadDrvStat];
			readRegisters[ReadDrvStat] = regVal;
			regVal &= oldDrvStat;
			accumulatedDriveStatus |= regVal;
		}
		else
		{
			readRegisters[previousRegIndexRequested] = regVal;
		}
	}

	// Deal with the stall status
	if (   (rcvDataBlock[0] & (1u << 2)) != 0							// if the status indicates stalled
		&& interval != 0
		&& interval <= maxStallStepInterval								// if the motor speed is high enough to get a reliable stall indication
	   )
	{
		readRegisters[ReadDrvStat] |= TMC51xx_RR_SG;
		accumulatedDriveStatus |= TMC51xx_RR_SG;
		EndstopOrZProbe::SetDriversStalled(driverBit);
	}
	else
	{
		readRegisters[ReadDrvStat] &= ~TMC51xx_RR_SG;
		EndstopOrZProbe::SetDriversNotStalled(driverBit);
	}

	previousRegIndexRequested = (regIndexBeingUpdated == NoRegIndex) ? regIndexRequested : NoRegIndex;
}

void Tmc51xxDriverState::TransferFailed() noexcept
{
	regIndexRequested = previousRegIndexRequested = NoRegIndex;
}

// State structures for all drivers
static Tmc51xxDriverState *driverStates;
static size_t baseDriveNo = 0;
// TMC51xx management task
static TASKMEM Task<TmcTaskStackWords> tmcTask;


DriversState Tmc51xxDriverState::SetupDriver(bool reset) noexcept
{
	if (reset)
	{
		accumulatedDriveStatus = 0;
		if (TMC_PINS[driverNumber] == NoPin)
			ready = false;
		else
		{
			numReads = 0;
			ready = true;
		}
		return DriversState::initialising;
	}
	if (numReads < NumReadRegisters)
		return 	DriversState::initialising;
	else
	{
		// check for invalid registers
		if (readRegisters[ReadGStat] == 0xffffffff && readRegisters[ReadMsCnt] == 0xffffffff && readRegisters[ReadPwmScale] == 0xffffffff &&
		     readRegisters[ReadPwmAuto] == 0xffffffff)
		{
			accumulatedDriveStatus = 0;
			for(size_t i = 0; i < NumReadRegisters; i++)
				readRegisters[i] = 0;
			ready = false;
			return DriversState::notInitialised;
		}
		else
			return DriversState::ready;
	}
}

static SharedSpiClient *spiDevice;

// Declare the DMA buffers with the __nocache attribute. Access to these must be aligned.
static __nocache uint8_t sendData[5];
static __nocache uint8_t rcvData[5];

extern "C" [[noreturn]] void TmcLoop(void *) noexcept
{
	for (;;)
	{
		if (driversState <= DriversState::noDrivers)
		{
			if (driversState != DriversState::noDrivers) driversState = DriversState::powerWait;
			TaskBase::Take();
		}
		else
		{
			if (driversState == DriversState::notInitialised)
			{
				for (size_t drive = 0; drive < numTmc51xxDrivers; ++drive)
				{
					driverStates[drive].SetupDriver(true);
					driverStates[drive].WriteAll();
				}
				driversState = DriversState::initialising;
			}
			else
			{
				if (driversState == DriversState::initialising)
				{
					// If all drivers that share the global enable have been initialised, set the global enable
					bool allInitialised = true;
					for (size_t i = 0; i < numTmc51xxDrivers; ++i)
					{
						if (driverStates[i].UpdatePending() || driverStates[i].SetupDriver(false) == DriversState::initialising)
						{
							allInitialised = false;
							break;
						}
					}

					if (allInitialised)
					{
						size_t readyCnt = 0;
						for (size_t driver = 0; driver < numTmc51xxDrivers; ++driver)
						{
							if (driverStates[driver].IsReady())
							{
								digitalWrite(ENABLE_PINS[driver+baseDriveNo], false);
								readyCnt++;
							}
						}
						driversState = (readyCnt ? DriversState::ready : DriversState::noDrivers);
					}
				}
			}
			if (!spiDevice->Select(100))
			{
				debugPrintf("TMC51xx: Failed to select spi device\n");
				continue;
			}		
			for (size_t i = 0; i < numTmc51xxDrivers; ++i)
			{
				if (driverStates[i].IsReady())
				{
					driverStates[i].GetSpiCommand(sendData);
					fastDigitalWriteLow(TMC_PINS[i+baseDriveNo]);
					spiDevice->TransceivePacket(sendData, rcvData, 5);
					fastDigitalWriteHigh(TMC_PINS[i+baseDriveNo]);
					driverStates[i].TransferSucceeded(rcvData);
				}
			}
			spiDevice->Deselect();
			// Give other tasks a chance to run.
			delay(1);
		}
	}
}

// Members of namespace SmartDrivers

// Initialise the driver interface and the drivers, leaving each drive disabled.
// It is assumed that the drivers are not powered, so driversPowered(true) must be called after calling this before the motors can be moved.
void Tmc51xxDriver::Init(size_t firstDrive, size_t numDrivers) noexcept
{
	numTmc51xxDrivers = min<size_t>(numDrivers, MaxSmartDrivers);
	baseDriveNo = firstDrive;
	if (numTmc51xxDrivers == 0)
	{
		driversState = DriversState::ready;
		return;
	}
	driversState = DriversState::noPower;
	driverStates = (Tmc51xxDriverState *)	Tasks::AllocPermanent(sizeof(Tmc51xxDriverState )*numTmc51xxDrivers);
	memset((void *)driverStates, 0, sizeof(Tmc51xxDriverState)*numTmc51xxDrivers);
	// make sure CS is not enabled and init everything
	for (size_t driver = 0; driver < numTmc51xxDrivers; ++driver)
	{
		new(&driverStates[driver]) Tmc51xxDriverState();
		if (TMC_PINS[driver+baseDriveNo] != NoPin)
			pinMode(TMC_PINS[driver+baseDriveNo], OUTPUT_HIGH);
		driverStates[driver].Init(driver+baseDriveNo);
	}
	spiDevice = new SharedSpiClient(SharedSpiDevice::GetSharedSpiDevice(SmartDriversSpiChannel), DriversSpiClockFrequency, SPI_MODE_3, NoPin, false);
	tmcTask.Create(TmcLoop, "TMC", nullptr, TaskPriority::TmcPriority);
}

// Shut down the drivers and stop any related interrupts
void Tmc51xxDriver::Exit() noexcept
{
	if (numTmc51xxDrivers > 0)
	{
		TurnDriversOff();
		tmcTask.TerminateAndUnlink();
	}
	driversState = DriversState::shutDown;						// prevent Spin() calls from doing anything
}


// Flag that the the drivers have been powered up or down
void Tmc51xxDriver::Spin(bool powered) noexcept
{
	if (numTmc51xxDrivers == 0) return;
	TaskCriticalSectionLocker lock;

	if (powered)
	{
		if (driversState == DriversState::powerWait)
		{
			driversState = DriversState::notInitialised;
			tmcTask.Give();									// wake up the TMC task because the drivers need to be initialised
		}
	}
	else if (driversState > DriversState::powerWait)
	{
		TurnDriversOff();
	}
}

// This is called from the tick ISR, possibly while Spin (with powered either true or false) is being executed
void Tmc51xxDriver::TurnDriversOff() noexcept
{
	for (size_t driver = 0; driver < numTmc51xxDrivers; ++driver)
	{
		digitalWrite(ENABLE_PINS[driver + baseDriveNo], true);
	}

	driversState = (driversState == DriversState::noDrivers ? DriversState::powerWait : DriversState::noPower);
}

bool Tmc51xxDriver::IsReady() noexcept
{
	return driversState == DriversState::ready || driversState == DriversState::noDrivers;
}


TmcDriverState* Tmc51xxDriver::GetDrive(size_t driveNo) noexcept
{
	return &(driverStates[driveNo]);
}

#endif

// End
