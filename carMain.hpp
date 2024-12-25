#pragma once

/*Libraries to include*/
#include <Arduino.h>
#include <FastLED.h>

/*Define Arduino Pins*/
#define mode_pin 2
#define STBY 3 //standby pin - must be HIGH to work
#define RGB_pin 4
#define PWMA 5 //"Speed" of LEFT motors
#define PWMB 6 //"Speed" of RIGHT motors
#define AIN1 7 //Power to LEFT motors
#define BIN1 8 //Power to RIGHT motors
#define IR 9 //define the IR receiving pin
#define servo_pin 10

#define echo 12
#define trig 13

/*for RGB_LED*/
#define numLEDs 1

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
void backup();
void autopilot(); //autopilot
void avoidance();
void distance_check();
void flash_led_red();
void make_led_yellow();
void make_led_pink();

/*global variables defined*/
extern float MotorSpeed;
extern int direction;