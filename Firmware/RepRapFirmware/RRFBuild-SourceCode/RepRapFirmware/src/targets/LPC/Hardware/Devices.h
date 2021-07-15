#ifndef SRC_STM32_HARDWARE_DEVICES_H_
#define SRC_STM32_HARDWARE_DEVICES_H_

#include <AsyncSerial.h>
typedef AsyncSerial UARTClass;

#include <USBSerial.h>
void DeviceInit() noexcept;
void StopAnalogTask() noexcept;

#endif /* SRC_STM32_HARDWARE_DEVICES_H_ */
