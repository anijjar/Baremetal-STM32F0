# Door Monitor

I need a door monitor for my store. Everything I have bought commercially has died too quickly. I could put a manual door bell on the door, but where is the fun in that.

The original idea was to use a microcontroller, such as an Atmel, but after some research, I discovered several unused IO pins on the HC05 module itself. Now, im going to dump the HC05 firmware and modify it so that on an external interrupt from a reed switch, it will send a message to one of the available tablets. The tablet will play an audiable beep, alerting my staff that the door is open and a client needs attending.

## Power Requirements
The HC05 module operates at 5V input, but the maximum operating characteristics is -0.4V to 5.6V. Ill use a coin cell as they come at 3V and at trickle current draw, can last a long time? (Needs some testing) Hopefully, I wont need to modify the system clock, cause I dont know what that will do to the bluetooth subsystems.

## Reed Switch
The reedswitch circuit will be a pull up switch, followed by a low pass filter to stop bouncing.

# References
https://pfalcon-oe.blogspot.com/2012/04/opensource-sensor-node-firmware-for.html
https://www.instructables.com/Upgrade-Your-3-Bluetooth-Module-to-Have-HID-Firmwa/
https://manuals.plus/banggood/banggood-hc-05-manual?expand_article=1

# Work Log

## 2023-08-30
Started the Project and got a working protoype with an Arduino Uno, HC05, and a push button. The sketch sends
"Open" and "Close" to a Bluetooth monitor on an Android phone. Now I am brainstorming next 
steps.

Brainstorm:
- I will need to reduce the power consumption of the circuit mounted on the door. I dont 
want to change the batteries for as long as possible; anything under a month would be 
unideal. The atmega328P has sleep modes to help reduce current consumption to microamps, 
but the downside is the large size of the chip. I want this device to have a small form
factor. I might have to reduce the size of the HC05 also. I have a few Attiny15L-1P0 
laying around. it has high clock speeds (1Mhz for ~3mA), but I will be slowing that down 
considerably. TLDR; I will use the Attiny and write some assembly code to slow down
the clock speed, thereby acheiving the small form factor as well as low power consumption.

- Now the issue with HC05. I have a high likely feeling that the firmware designers 
have it setup to work at full power to make it appealing for the normie user;
I am not no normie user. The formfactor is not too bad, I may cut the pins to make it
less protrusive. Looks like I need to read the datasheet for its nominal power consumption
and probably make some changes to its clock speed and transmision power. Fun.

- Regarding the tiny, I will need one input pin and some serial transmit pin for the 
HC05. PB2 can be external interrupt input. There does not look like this thing has 
any serial output, so I will need to replicate it in firmware. More Fun.

- I will need a HQ for the HC05 to transmit to and also lock it somehow so nobody can find it
or connect with it. I already changed the password to something more secure, but I would like
it to be undiscoverable. I think one of the AT commands have something, but im not too sure.
I could make a simple android program to run in the background on one of the tablets, that 
way I dont have to build a buzzer circuit or get another HC05. The downside is that the 
staff may not hear the bell from the office. I think this may be the best solution though, 
and just keep the volume up. The tablets each have their own addresses also, so I can 
preset the HC05 to wirelessly connect to that device only. Adding more security. Rather than
a program, maybe I can experiment with processes. 

- For power, the best bet would be three AA batteries. Each battery is 1.5V, equating to 4.5V
which is enough for the Tiny and HC05. The HC05 takes a 5V input and regulates it down to 1.8-
3.6V. When AA are dead, they are at 1.3V. 3 AA at 1.3V is 3.9V, enough to stay above the danger
zone for both devices. 3AA also have a nice form factor. Crap, AA are the same size as the PDIP
Atmega chips, should I just use them then... Ugh the decisions.

- After reviewing the HC05 datasheet, it appears there are many IO pins that are not being used.
I like to hear that. Also, apparently we can make the HC05 into an HID device through some 
magic. I think Ill do my way.

# 2023-09-15 

- The HC05 operates in the mAs range to transmit, which will not work for battery powered IOT. I need something in microamp range. A Bluetooth LE module that has IO, low power modes, and has an ARM micro... nice.

