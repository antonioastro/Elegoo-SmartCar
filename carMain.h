#pragma once

/*Libraries to include*/
#include <Arduino.h>

/*Define Arduino Pins*/
#define STBY 3 //standby pin - must be HIGH to work

#define PWMA 5 //"Speed" of LEFT motors
#define PWMB 6 //"Speed" of RIGHT motors
#define AIN1 7 //Power to LEFT motors
#define BIN1 8 //Power to RIGHT motors
#define IR 9 //define the IR receiving pin

/*functions defined*/
void forward(); //carFunctions
void stop();
void turn_left(); 
void turn_right();
void reverse();
void check_speed();
void rotate90left();
void rotate90right();
void increase_speed(); //remoteControl
void decrease_speed();
void reset_speed();
void direction_check();

/*global variables defined*/
extern float MotorSpeed;
extern int direction;

/*global classes defined*/