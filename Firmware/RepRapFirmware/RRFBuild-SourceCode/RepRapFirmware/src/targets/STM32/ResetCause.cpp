#include "SoftwareReset.h"
#include "ResetCause.h"
#include "RepRapFirmware.h"

static ResetCause_t ResetCause = RESET_CAUSE_UNKNOWN;


void InitResetCause() noexcept
{

    if (__HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST))
    {
        ResetCause = RESET_CAUSE_LOW_POWER_RESET;
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST))
    {
        ResetCause = RESET_CAUSE_WINDOW_WATCHDOG_RESET;
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST))
    {
        ResetCause = RESET_CAUSE_INDEPENDENT_WATCHDOG_RESET;
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST))
    {
        ResetCause = RESET_CAUSE_SOFTWARE_RESET; // This reset is induced by calling the ARM CMSIS `NVIC_SystemReset()` function!
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST))
    {
        ResetCause = RESET_CAUSE_POWER_ON_POWER_DOWN_RESET;
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST))
    {
        ResetCause = RESET_CAUSE_EXTERNAL_RESET_PIN_RESET;
    }
    // Needs to come *after* checking the `RCC_FLAG_PORRST` flag in order to ensure first that the reset cause is 
    // NOT a POR/PDR reset. See note below. 
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_BORRST))
    {
        ResetCause = RESET_CAUSE_BROWNOUT_RESET;
    }
    else
    {
        ResetCause = RESET_CAUSE_UNKNOWN;
    }

    // Clear all the reset flags or else they will remain set during future resets until system power is fully removed.
    __HAL_RCC_CLEAR_RESET_FLAGS();
}

ResetCause_t GetResetCause() noexcept
{
    return ResetCause;
}
