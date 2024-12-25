#include "carMain.hpp"

int direction;

/*Functions only used in remote-control of the car*/
void increase_speed(){
  if (MotorSpeed<255){
    MotorSpeed=MotorSpeed+20;
  }
  direction_check();
}

void decrease_speed(){
  if (MotorSpeed>55){
   MotorSpeed=MotorSpeed-20;
  }
  direction_check(); //applies the new speed, and resumes the current direction of motion.
}

void reset_speed(){
  MotorSpeed=75;
}

void backup(){
  reverse();
  delay(1000);
  if (random(1,10)<=5){
    rotate90left();
   }
   else{
    rotate90right();
  } 
}

/*functions used as a sub-function of the above, but not required elsewhere*/
void direction_check(){ //direction_check only occurs as a subfunction of increase_ and decrease_speed
  if(direction==0){
    forward();
  }
  if(direction==1){
    reverse();
  }
  if(direction==2){
    stop();
  }
  if(direction==3){
    turn_left();
  }
  if(direction==4){
    turn_right();
  }
}