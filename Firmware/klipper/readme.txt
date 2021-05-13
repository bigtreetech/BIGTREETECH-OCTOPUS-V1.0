klipper：
1. The configuration file is done, which can be configuration file of the klipper 3D printer 
2. Raspberry Pi compile firmware (parameters are as screenshots)
3. Connect the motherboard with the Raspberry Pi in DFU mode to boot the firmware which is compiled well by klipper (you need to press the reset button to make the Raspberry Pi recognize it after power on)
4. After exiting the DFU mode and resetting,then restart the klipper service to use it. If the USB is disconnected during the use of the klipper, the klipper service of the Raspberry Pi will run abnormally. You need to manually restart the klipper background service on the Raspberry Pi or directly restart the Raspberry Pi. 
