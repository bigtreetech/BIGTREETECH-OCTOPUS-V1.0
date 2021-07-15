#ifndef TMCDRIVERSTATE_H
#define TMCDRIVERSTATE_H
#include "StepperDrivers/DriverMode.h"


class TmcDriverState
{
public:
	virtual void SetAxisNumber(size_t p_axisNumber) noexcept;
	virtual uint32_t GetAxisNumber() const noexcept = 0;
	virtual bool SetMicrostepping(uint32_t shift, bool interpolate) noexcept = 0;
	virtual unsigned int GetMicrostepping(bool& interpolation) const noexcept = 0;
	virtual bool SetDriverMode(unsigned int mode) noexcept = 0;
	virtual DriverMode GetDriverMode() const noexcept = 0;
	virtual void SetCurrent(float current) noexcept = 0;
	virtual void Enable(bool en) noexcept = 0;
	virtual void AppendDriverStatus(const StringRef& reply) noexcept = 0;
#if HAS_STALL_DETECT
	virtual void SetStallDetectThreshold(int sgThreshold) noexcept = 0;
	virtual void SetStallDetectFilter(bool sgFilter) noexcept = 0;
	virtual void SetStallMinimumStepsPerSecond(unsigned int stepsPerSecond) noexcept = 0;
	virtual void AppendStallConfig(const StringRef& reply) const noexcept = 0;
#endif
	virtual bool SetRegister(SmartDriverRegister reg, uint32_t regVal) noexcept = 0;
	virtual uint32_t GetRegister(SmartDriverRegister reg) const noexcept = 0;

	virtual float GetStandstillCurrentPercent() const noexcept = 0;
	virtual void SetStandstillCurrentPercent(float percent) noexcept = 0;

	virtual uint32_t ReadLiveStatus() const noexcept = 0;
	virtual uint32_t ReadAccumulatedStatus(uint32_t bitsToKeep) noexcept = 0;
};
#endif