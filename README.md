# Elegoo-SmartCar
Continuing to develop my program for the Elegoo SmartCar v4 using the Elegoo Smartcar Shield v1.1 and an Arduino Uno R3. 

This is NOT yet the final product, but now has its own repository due to my plans to create a more modular approach to programming the car using multiple .cpp and .h files. I think this will make it easier for me to develop the code, and upload updates as development continues.

This does not yet have the full functionality of the latest version in my Elegoo-SmartCar-Dev repository while I continue to learn how to properly use header files in C++

Car_separate_files.ino - is the main ino file to open and compile in Arduino
carFunctions.cpp - contains all of the core functions for the car that are needed regardless of the mode (remote control IR or WiFi, or Autopilot, or LineTrack)
remoteControl.cpp - contains all of the functions needed for remote control, either IR or WiFi. Currently the *main* function for IRcontrol is in the main ino file until I can get this working as intended.
remoteHexValues.h - contains the hex values for the keys on my remote.
carMain.h - the main header file for the program that links all of the files together. It declares all of the functions from all files and any global variables.

_Coming soon_
carCosmetics.cpp - contains functions for controlling the onboard RGB lighting
autopilot.cpp - contains all functions needed only for the object avoidance and automatic patrol of the car

All files contain some comments but aren't necessarily complete or may not make sense to you. Please start a discussion if you have any questions about my program!
