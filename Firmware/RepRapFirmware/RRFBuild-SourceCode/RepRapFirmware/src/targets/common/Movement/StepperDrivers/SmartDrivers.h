/*
 * This is the public interface to TMC Smart drivers. Currently
 * We support TMC22xx and TMC51xx devices. 
 * 
 * Author: GA
 */


#ifndef SRC_MOVEMENT_STEPPERDRIVERS_SMARTDRIVERS_H_
#define SRC_MOVEMENT_STEPPERDRIVERS_SMARTDRIVERS_H_

#include "RepRapFirmware.h"

#if SUPPORT_TMC51xx || SUPPORT_TMC22xx

#include "StepperDrivers/DriverMode.h"

// DRV_STATUS register bit assignments
// Note: These values are identical to those used by TMC22XX devices.
// All other devices must convert the return from GetAccumulatedStatus() to match
const uint32_t TMC_RR_OT = 1u << 1;			// over temperature shutdown
const uint32_t TMC_RR_OTPW = 1u << 0;		// over temperature warning
const uint32_t TMC_RR_S2G = 15u << 2;		// short to ground counter (4 bits)
const uint32_t TMC_RR_OLA = 1u << 6;		// open load A
const uint32_t TMC_RR_OLB = 1u << 7;		// open load B
const uint32_t TMC_RR_SG = 1u << 12;		// this is a reserved bit, which we use to signal a stall
const uint32_t TMC_RR_STST = 1u << 31;      // driver standstill
namespace SmartDrivers
{
	void Init(size_t numSmartDrivers) noexcept;
	void Exit() noexcept;
	void Spin(bool powered) noexcept;
	void TurnDriversOff() noexcept;
	bool IsReady() noexcept;

	void SetAxisNumber(size_t driver, uint32_t axisNumber) noexcept;
	uint32_t GetAxisNumber(size_t drive) noexcept;
	void SetCurrent(size_t driver, float current) noexcept;
	void EnableDrive(size_t driver, bool en) noexcept;
	uint32_t GetLiveStatus(size_t driver) noexcept;
	uint32_t GetAccumulatedStatus(size_t drive, uint32_t bitsToKeep) noexcept;
	bool SetMicrostepping(size_t drive, unsigned int microsteps, bool interpolation) noexcept;
	unsigned int GetMicrostepping(size_t drive, bool& interpolation) noexcept;
	bool SetDriverMode(size_t driver, unsigned int mode) noexcept;
	DriverMode GetDriverMode(size_t driver) noexcept;
	void SetStallThreshold(size_t driver, int sgThreshold) noexcept;
	void SetStallFilter(size_t driver, bool sgFilter) noexcept;
	void SetStallMinimumStepsPerSecond(size_t driver, unsigned int stepsPerSecond) noexcept;
	void AppendStallConfig(size_t driver, const StringRef& reply) noexcept;
	void AppendDriverStatus(size_t driver, const StringRef& reply) noexcept;
	float GetStandstillCurrentPercent(size_t driver) noexcept;
	void SetStandstillCurrentPercent(size_t driver, float percent) noexcept;
	bool SetRegister(size_t driver, SmartDriverRegister reg, uint32_t regVal) noexcept;
	uint32_t GetRegister(size_t driver, SmartDriverRegister reg) noexcept;
	GCodeResult GetAnyRegister(size_t driver, const StringRef& reply, uint8_t regNum) noexcept;
	GCodeResult SetAnyRegister(size_t driver, const StringRef& reply, uint8_t regNum, uint32_t regVal) noexcept;
	bool IsReady() noexcept;
#if HAS_STALL_DETECT
	DriversBitmap GetStalledDrivers(DriversBitmap driversOfInterest) noexcept;
#endif
};

#endif

#endif /* SRC_MOVEMENT_STEPPERDRIVERS_SMARTDRIVERS_H_ */
