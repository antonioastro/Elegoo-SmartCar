#include "carMain.hpp"

/* This file contains the basic functions of the car used across all modes

---CONTROLLING THE MOTORS--- both motors A and B have 2 inputs. IN2 is not connected to Arduino, it is always opposite of IN1.
IN1 	IN2 	Mode
HIGH  LOW   Clockwise
LOW 	HIGH 	Counterclockwise

---DIRECTIONALS---
Dir     Motor A   Motor B
FORWARD HIGH      HIGH
REVERSE LOW       LOW
LEFT    HIGH      LOW
RIGHT   LOW       HIGH

*/

float MotorSpeed = 75; //MotorSpeed is accessed only within carFunctions.cpp
static float TurnSpeed; //TurnSpeed is only used in turn_left or _right, and is intended to apply a limit to the rate of rotation for ease of use.
static float SaveMotorSpeed; //To clone MotorSpeed when it must be overwritten.

void forward(){
  analogWrite(PWMA,MotorSpeed);
  analogWrite(PWMB,MotorSpeed);
  digitalWrite(AIN1,HIGH);
  digitalWrite(BIN1,HIGH);
}

void stop(){
  analogWrite(PWMA,0);
  analogWrite(PWMB,0);
}

void turn_left(){
  check_speed(); 
  digitalWrite(AIN1,HIGH);
  digitalWrite(BIN1,LOW);
  analogWrite(PWMA,TurnSpeed);
  analogWrite(PWMB,TurnSpeed);
}
 
void turn_right(){ 
  check_speed();
  digitalWrite(AIN1,LOW);
  digitalWrite(BIN1,HIGH);
  analogWrite(PWMA,TurnSpeed);
  analogWrite(PWMB,TurnSpeed);
}

void reverse(){
  digitalWrite(AIN1,LOW);
  digitalWrite(BIN1,LOW);
  analogWrite(PWMA,MotorSpeed);
  analogWrite(PWMB,MotorSpeed);
}

void rotate90left(){ //calibrated to rotate the car exactly 90 degrees to the left when MotorSpeed is 75
  SaveMotorSpeed = MotorSpeed;
  MotorSpeed=75;
  turn_left();
  delay(1000);
  stop();
  MotorSpeed=SaveMotorSpeed;
}

void rotate90right(){ //calibrated to rotate the car exactly 90 degrees to the right when MotorSpeed is 75
  SaveMotorSpeed = MotorSpeed;
  MotorSpeed=75;
  turn_right();
  delay(1000);
  stop();
  MotorSpeed=SaveMotorSpeed;
}

/*functions used as a sub-function of the above, but not required elsewhere*/
void check_speed(){ //applies a limit to the rate of turning, for ease of use.
  if (MotorSpeed>115){
    TurnSpeed=115;
  }
  else{
    TurnSpeed=MotorSpeed;
  }
}