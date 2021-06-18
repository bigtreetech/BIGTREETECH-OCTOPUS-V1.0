# F446-OctoPus

## 基于最新的 V3.3 版本修改
0. (563KB) V3.3  F407版本标准的预编译固件尺寸是 563KB
1. (-4KB) 删除其他主板的pin脚表，只保留OctoPus的pin 脚分配表
2. (-4KB) 删除其他主板的SD卡检测，只保留OctoPus的SDIO   
3. (-5KB) 删除MCU温度检测和电压监控
4. (-3KB) 禁用加速度计功能
5. (-24KB) 禁用LCD12864功能
6. (-2KB) 禁用TRACK_OBJECT_NAMES功能
7. (-9KB) 删除给panelDue更新固件的Bossa功能
8. (-32KB) 删除 NVMEmulation 功能(存储温度较准和复位数据)，此功能相当于log日志区，删除后无法保存异常数据以便复位后诊断

- 删除以上功能后编译出的二进制文件有 480KB，STM32F446ZE Flash = 512KB - 32KB(bootloader) = 480KB
- 注意：需要使用最新版的引导程序


## Modification based on the latest V3.3 version
0. (563KB) the pre compiled firmware size of v3.3 F407 is 563KB
1. (-4KB) Delete the pin table of other motherboards, and only retain the pin allocation table of OctoPus
2. (-4KB) Delete the SD card check of other motherboards, and only retain the SDIO of OctoPus
3. (-5KB) Delete MCU temperature detection and voltage monitoring (Disable HAS_CPU_TEMP_SENSOR and HAS_VOLTAGE_MONITOR)
4. (-3KB) Disable SUPPORT_ACCELEROMETERS
5. (-24KB) Disable SUPPORT_12864_LCD
6. (-2KB) Disable TRACK_OBJECT_NAMES
7. (-9KB) Delete the Bossa feature (to update the firmware of panelDue)
8. (-32KB) Delete the NVMEmulation feature (store thermistorCalibration and resetData), which is equivalent to the log area, Abnormal data cannot be saved for diagnosis after reset when deleted

- After deleting the above functions, the compiled binary file is 480KB，STM32F446ZE Flash = 512KB - 32KB(bootloader) = 480KB
- Note: you need to use the latest version of the bootloader
