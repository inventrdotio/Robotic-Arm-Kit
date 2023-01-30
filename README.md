# Robotic-Arm-Kit
Official Repo for the InventrKits Robotic Arm Kit from inventr.io

## Joystick shield
The latest kit comes with a Joystick Shield that will work with any Arduino Uno compatible boards.  It includes two dual-axis PS2 style Joysticks with X/Y Analog potentiometers and a push button.  The shield also includes pins for easy attachment of 3-pin SG-90 servos (included in robotic arm kit) and an LED.

Shield notes:

There are pin "triplets" on the shield with GND, 5v and Signal which make it easy to connect the SG-90 servos.  The signal pins connect to Arduino data pins D5, D6, D7, D9, D10, D12.

Triplet pads (with no pins soldered in) exist in similar fashion for Arduino pins D8, A4, A5.

Unsoldered pads exist where pins could be soldered on for 5v(3), 3.3v(3), GND(4).

## Joystick control pins

Left joystick horizontal: A0		(left=0, right=1023)
Left joystick vertical: A1		(down=1023, up=0)  <====
Right joystick horizontal: A3	(left=0, right=1023)
Right joystick vertical: A2		(down=1023, up=0)  <====

Left button: pin 2, LOW when pushed
Right button: pin 4, LOW when pushed

## On-board LED (red)

LED on pin 3.  Not sure of resistor value and if it's connected to the LED the traces aren't on the top or bottom layers of the board.  The LED is probably wire to ground through the resistor via an internal board layer.