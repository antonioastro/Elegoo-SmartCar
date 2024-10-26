#include "carMain.h"
#include "remoteHexValues.h"
#include <IRremote.h>

IRrecv irrecv(IR);
decode_results results; //not sure why, but all the stuff for the IR Remote needs to be in the main ino file. Want to fix and put in IRremote.cpp

void setup(){
  Serial.begin(9600);

  pinMode(STBY,OUTPUT);
  pinMode(PWMA,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(BIN1,OUTPUT);

  digitalWrite(STBY,HIGH);

  irrecv.enableIRIn(); //enable the IR detection
  irrecv.blink13(true); //this will flash the built in LED to show a signal is received
}

void loop(){
  IRcontrol();
}

/*Functions for IR remote below - want to move to own .cpp file eventually, but this isn't working atm*/
void IRcontrol(){
  if(irrecv.decode(&results)){ //check to see if an IR signal is received
    switch(results.value){ //do something depending on the "HEX value" of the key pressed
      case UP: //intitially tested these on the HEX values, then converted to DEC - the same effect, so it doesn't matter if HEX or DEC. Needs changing for each remote used.
        forward(); //Up
        direction=0; //each time a button is pressed that is directional, the direction int will update.
        break;
      case DOWN: //Down
        reverse();
        direction=1;
        break;
      case SELECT:
        stop();
        direction=2;
        break;
      case LEFT: //Left
        turn_left();
        direction=3;
        break;
      case RIGHT: //Right
        turn_right();
        direction=4;
        break;
      case CHANNEL_UP:
        increase_speed();
        break;
      case CHANNEL_DOWN:
        decrease_speed();
        break;
      case HELP:
        reset_speed();
        break;
      case BACKUP:
        backup();
        break;
    }
  }
}