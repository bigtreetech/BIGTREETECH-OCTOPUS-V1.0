/*
 * FilamentSensor.h
 *
 *  Created on: 20 Jul 2017
 *      Author: David
 */

#ifndef SRC_FILAMENTSENSORS_FILAMENTMONITOR_H_
#define SRC_FILAMENTSENSORS_FILAMENTMONITOR_H_

#include <RepRapFirmware.h>
#include <Hardware/IoPorts.h>
#include <ObjectModel/ObjectModel.h>
#include <RTOSIface/RTOSIface.h>

#if defined(DUET3) || defined(DUET3MINI)
# include <Duet3Common.h>
#else
# include <General/NamedEnum.h>
NamedEnum(FilamentSensorStatus, uint8_t,
	noMonitor,
	ok,
	noDataReceived,
	noFilament,
	tooLittleMovement,
	tooMuchMovement,
	sensorError
);
#endif

#if SUPPORT_CAN_EXPANSION
class CanMessageFilamentMonitorsStatus;
#endif

class FilamentMonitor INHERIT_OBJECT_MODEL
{
public:
	FilamentMonitor(const FilamentMonitor&) = delete;

	// Configure this sensor, returning true if error and setting 'seen' if we processed any configuration parameters
	virtual GCodeResult Configure(GCodeBuffer& gb, const StringRef& reply, bool& seen) THROWS(GCodeException) = 0;

	// Call the following at intervals to check the status. This is only called when extrusion is in progress or imminent.
	// 'filamentConsumed' is the net amount of extrusion since the last call to this function.
	virtual FilamentSensorStatus Check(bool isPrinting, bool fromIsr, uint32_t isrMillis, float filamentConsumed) noexcept = 0;

	// Clear the measurement state - called when we are not printing a file. Return the present/not present status if available.
	virtual FilamentSensorStatus Clear() noexcept = 0;

	// Print diagnostic info for this sensor
	virtual void Diagnostics(MessageType mtype, unsigned int extruder) noexcept = 0;

	// ISR for when the pin state changes. It should return true if the ISR wants the commanded extrusion to be fetched.
	virtual bool Interrupt() noexcept = 0;

	// Call this to disable the interrupt before deleting a filament monitor
	virtual void Disable() noexcept;

	// Override the virtual destructor if your derived class allocates any dynamic memory
	virtual ~FilamentMonitor() noexcept;

	// Return the type of this sensor
	unsigned int GetType() const noexcept { return type; }

	// Check that this monitor still refers to a valid extruder
	bool IsValid() const noexcept;

	// Get the status of the filament monitor as a string
	const char *GetStatusText() const noexcept { return lastStatus.ToString(); }

	// Static initialisation
	static void InitStatic() noexcept;

	// Poll the filament sensors
	static void Spin() noexcept;

	// Check the drive assignments. Called when M584 may have been used to remap extruder drives. Return true if we need to output the warning appended to 'reply'.
	static bool CheckDriveAssignments(const StringRef& reply) noexcept;

	// Close down the filament monitors, in particular stop them generating interrupts. Called when we are about to update firmware.
	static void Exit() noexcept;

	// Handle M591
	static GCodeResult Configure(GCodeBuffer& gb, const StringRef& reply, unsigned int extruder) THROWS(GCodeException)
	pre(extruder < MaxExtruders; extruder < reprap.GetGCodes().GetNumExtruders());

	// Send diagnostics info
	static void Diagnostics(MessageType mtype) noexcept;

#if SUPPORT_OBJECT_MODEL
	// Get the number of monitors to report in the OM
	static size_t GetNumMonitorsToReport() noexcept;

	// Get access to a filament monitor when we already have a read lock
	static FilamentMonitor *GetMonitorAlreadyLocked(size_t extruder) noexcept { return filamentSensors[extruder]; }
#endif

#if SUPPORT_CAN_EXPANSION
	static void UpdateRemoteFilamentStatus(CanAddress src, CanMessageFilamentMonitorsStatus& msg) noexcept;
#endif

	// This must be public so that the array descriptor in class RepRap can lock it
	static ReadWriteLock filamentMonitorsLock;

protected:
	FilamentMonitor(unsigned int extruder, unsigned int t) noexcept;

	GCodeResult CommonConfigure(GCodeBuffer& gb, const StringRef& reply, InterruptMode interruptMode, bool& seen) THROWS(GCodeException);

	const IoPort& GetPort() const noexcept { return port; }
	bool HaveIsrStepsCommanded() const noexcept { return haveIsrStepsCommanded; }

	static int32_t ConvertToPercent(float f)
	{
		return lrintf(100 * f);
	}

	bool IsLocal() const noexcept { return driver.IsLocal(); }

private:

	// Create a filament sensor returning null if not a valid sensor type
	static FilamentMonitor *Create(unsigned int extruder, unsigned int monitorType, GCodeBuffer& gb, const StringRef& reply) noexcept;
	static void InterruptEntry(CallbackParameter param) noexcept;

	static FilamentMonitor *filamentSensors[MaxExtruders];

	int32_t isrExtruderStepsCommanded;
	uint32_t lastIsrMillis;
	unsigned int extruderNumber;
	unsigned int type;
	IoPort port;
	DriverId driver;

	bool isrWasPrinting;
	bool haveIsrStepsCommanded;
	FilamentSensorStatus lastStatus;
#if SUPPORT_CAN_EXPANSION
	bool hasRemote;
#endif
};

#endif /* SRC_FILAMENTSENSORS_FILAMENTMONITOR_H_ */
