Button Library for Arduino
==============
Button library v0.1
This library can provide debounced button presses without interrupting other functions in the loop. yay.

It will also allow to recognize multiple button taps (within a short time) and long held buttons.

It builds on ideas used by Jeff Saltzman on arduino forum: http://forum.arduino.cc/index.php?topic=14479.0

Usage Note
==============
If you use this as buttons which pull the voltage up when pushed then you will need to add pulldown resistors to the digital pins.
However if you use buttons which pull the voltage to ground when activated this library will automatically enable the avr's internal pullup resistors.
Also avoid using any pins if they have an LED attached (e.g. built in LED on most arduinos - pin 13 - See https://www.arduino.cc/en/Tutorial/DigitalPins note in section "Properties of Pins Configured as INPUT_PULLUP")
Also worth noting that a push and hold started before millis overflows and finishing after probably won't work.

Installation
==============
Copy this into your "[...]/MySketches/libraries/" folder and restart the Arduino editor.

*Happy Coding!*
