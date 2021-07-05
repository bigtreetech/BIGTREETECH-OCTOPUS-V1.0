# VORON 2.4 – BTT OctoPus Wiring Diagram

## NOTE
The configuration of RRF and Klipper firmware in this path is set according to this wiring. After the wiring is completed according to this diagram, the prepared `firmware.bin` and configuration file can work normally

## BTT OctoPus – Initial Preparation
<img src=Images/jumper.jpg width="1600" /><br/>
* Green – Add Jumper
* Red – Remove Jumper 
* ① Insert only the jumper in the Green and remove the other three jumpers in the Red in order to use TMC2209 UART mode.
* ② Remove all the jumpers of DIAG to avoid the influence of TMC2209 DIAG on the endstop.
* ③ Remove the USB 5V power supply jumper to avoid the interaction between the USB 5V of raspberry pi and the DC-DC 5V of the motherboard.
* ④ Insert all the jumpers into V_FUSED to set the fan voltage to the system supply voltage.
* ⑤ Insert the jumper into V_FUSED to set the probe voltage to the system supply voltage.

## Wiring diagram
<img src=Images/wiring.jpg width="1600" /><br/>
