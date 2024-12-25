#include "carMain.hpp"

#include "skyRemoteHexValues.hpp" //replace this with huluRemoteHexValues.hpp if using this remote
#include <IRremote.h>
#include <Servo.h>

IRrecv irrecv(IR);
decode_results results; //not sure why, but all the stuff for the IR Remote needs to be in the main ino file. Want to fix and put in IRremote.cpp

struct CRGB leds[numLEDs];
int led_red_loop = 0;

int mode_number = 0;

Servo scanner;
float pos = 40;
float distance;
float pulse_time;
int hit = 20;

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

  pinMode(mode_pin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(mode_pin),mode_switch,FALLING);

  pinMode(RGB_pin,OUTPUT);
  FastLED.addLeds<WS2812, RGB_pin, GRB>(leds,numLEDs);

  scanner.attach(servo_pin);
}

void loop(){
  switch(mode_number){
    case 0:
      IRcontrol(); //PINK
      break;
    case 1: 
      autopilot(); //YELLOW
      break;
  }
}

void mode_switch(){
  stop();
  if (mode_number<1){
    mode_number++;
  } else if (mode_number==1){
    mode_number=0;
  }
}

/*Functions for IR remote below - want to move to own .cpp file eventually, but this isn't working atm*/
void IRcontrol(){
  //scanner.write(90);
  make_led_pink();
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

void autopilot(){
  MotorSpeed=75; //autopilot runs at a slow speed to ensure it functions correctly.
  for (pos=30; pos<=150; pos=pos+2){ //scan constantly between 30 and 150deg
    scanner.write(pos);
    distance_check();
    avoidance(); //check to see if an avoidance manouevure is needed
    delay(5); //a delay of 5ms is needed otherwise the servo does not have time to turn.
  }

  for (pos=150; pos>=30; pos=pos-2){ //scan constantly from 150 back to 30deg
    scanner.write(pos);
    distance_check();
    avoidance(); //check to see if an avoidance manouevure is needed - otherwise move forward. this is entirely embedded within this function
    delay(5);
  }
}

void distance_check(){ 
  digitalWrite(trig,LOW);
  delayMicroseconds(2); //this guarantees no signal is currently being sent
  digitalWrite(trig,HIGH);
  delayMicroseconds(10); //send a 10us long burst of ultrasonic pulses -- this can be higher or lower, but 10us seems to work best
  digitalWrite(trig,LOW);

  pulse_time = pulseIn(echo,HIGH); //look for echo to run high - counts in us

  distance = 0.5*pulse_time*0.0343;
  return distance; //distance in cm
}

void avoidance(){
  if (distance<hit && pos==90){ //if obstacle is ahead, reverse slightly and turn left 90 degrees
    reverse();
    flash_led_red(); //the flash LED Red is a cosmetic change that flashes the LED Red to signify that a collision was about to occur and it is now running an avoidance manoevure.
    if (random(1,10)<=5){
      rotate90left();
    }
    else{
      rotate90right();
    }
  }
  if (distance<hit && pos<90){ //turn left if obstacle is on the right
    turn_left(); 
  }
  if (distance<hit && pos>90){ //turn right if obstacle is on the left
    turn_right();
  }
  if (distance>hit){ //only move forward if there is no obstacle within range
    forward();
    make_led_yellow();
  }
}

void flash_led_red(){ //this is configured to run approx 1000ms.
  leds[0]= CRGB::Red; //write the colour to a certain LED in the chain. Can change 0 to be any number if you have an array
  for (led_red_loop=0;led_red_loop<=5; led_red_loop++){ //loops OFF then ON 5 times, for a total of 1000ms
    FastLED.setBrightness(0); //OFF
    FastLED.show(); //instructs the WS2812 to write the changes to the LEDs
    delay(200);
    FastLED.setBrightness(255); //ON
    FastLED.show(); //instructs the WS2812 to write the changes to the LEDs
    delay(200);
  }
}

void make_led_yellow(){
  leds[0]= CRGB::Yellow; //write the colour to a certain LED in the chain. Can use CRGB(FF,FF,FF) instead, but the CRGB has pre-defined colours which is easier.
  FastLED.show(); //instructs the WS2812 to write the changes to the LEDs
}

void make_led_pink(){
  leds[0]= CRGB::DeepPink; //write the colour to a certain LED in the chain. Can use CRGB(FF,FF,FF) instead, but the CRGB has pre-defined colours which is easier.
  FastLED.show(); //instructs the WS2812 to write the changes to the LEDs
}