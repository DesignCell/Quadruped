
// JSU 2016.02.09

#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int pos;
int up; //up
int vert;// Nominal vertical
int dcnt; //Delay
int off[8];
#define SERVOMIN  150 // this is the 'minimum' pulse length count (150 out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (600 out of 4096)

void setup() {
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

//  (5)(1)  (3)(7)
//
//  (4)(0)  (2)(6)

//Horizontal: Front-Back
//Home=45° Min=15° Max=135°
off[0] = 0;
off[1] = 15;
off[2] = -5;
off[3] = -10;
//Vertical: Up-Down
//Home=90° Min=45° Max=135°
off[4] = -20;
off[5] = 5;
off[6] = -5;
off[7] = -15;

delay(250);
//Vertical-Up
pos=130;
  pwm.setPWM(4,0,map(pos+off[4],180,0,SERVOMIN, SERVOMAX));
  pwm.setPWM(5,0,map(pos+off[5],0,180,SERVOMIN, SERVOMAX));
  pwm.setPWM(6,0,map(pos+off[6],0,180,SERVOMIN, SERVOMAX));
  pwm.setPWM(7,0,map(pos+off[7],180,0,SERVOMIN, SERVOMAX));
  delay(250);
//Forward-Initial Position
  pwm.setPWM(0,0,map(40+off[0],0,180,SERVOMIN, SERVOMAX));
  pwm.setPWM(1,0,map(55+off[1],180,0,SERVOMIN, SERVOMAX));
  pwm.setPWM(2,0,map(50+off[2],180,0,SERVOMIN, SERVOMAX));
  pwm.setPWM(3,0,map(45+off[3],0,180,SERVOMIN, SERVOMAX));
  delay(500);
//Vertical-Home
vert=55;
  pwm.setPWM(4,0,map(vert+off[4],180,0,SERVOMIN, SERVOMAX));
  pwm.setPWM(5,0,map(vert+off[5],0,180,SERVOMIN, SERVOMAX));
  pwm.setPWM(6,0,map(vert+off[6],0,180,SERVOMIN, SERVOMAX));
  pwm.setPWM(7,0,map(vert+off[7],180,0,SERVOMIN, SERVOMAX));
  delay(1000);
}

void loop() {
up=35; //up (degress)
vert=55;
dcnt=30; //delay cnt (ms)

//Loop 1
//Start
//0 40+
//1 55-
//2 50+
//3 45-
for (int cnt = 1; cnt <6; cnt++){
  pwm.setPWM(0,0,map(40+cnt+off[0],0,180,SERVOMIN, SERVOMAX));
  pwm.setPWM(1,0,map(55-cnt+off[1],180,0,SERVOMIN, SERVOMAX));
  pwm.setPWM(2,0,map(50+cnt+off[2],180,0,SERVOMIN, SERVOMAX));
  pwm.setPWM(3,0,map(45-cnt+off[3],0,180,SERVOMIN, SERVOMAX));
  delay(dcnt);
}

//Loop 2
//Start
//0 45+
//1 50-
//2 55+//resetting
//3 40-
//Reset 2/6
pwm.setPWM(6,0,map(vert+up+off[6],0,180,SERVOMIN, SERVOMAX)); //Up
delay(dcnt);
pwm.setPWM(2,0,map(35+off[2],180,0,SERVOMIN, SERVOMAX)); //Reset forward
//Leave up
for (int cnt = 1; cnt <6; cnt++){
  pwm.setPWM(0,0,map(45+cnt+off[0],0,180,SERVOMIN, SERVOMAX));
  pwm.setPWM(1,0,map(50-cnt+off[1],180,0,SERVOMIN, SERVOMAX));
  //pwm.setPWM(2,0,map(55+cnt+off[2],180,0,SERVOMIN, SERVOMAX));//resetting
  pwm.setPWM(3,0,map(45-cnt+off[3],0,180,SERVOMIN, SERVOMAX));
  delay(dcnt);
}
  pwm.setPWM(6,0,map(vert+off[6],0,180,SERVOMIN, SERVOMAX)); //Drop back down
  delay(dcnt);

//Loop 3
//Start
//0 50+
//1 45-
//2 35+
//3 35-//resetting
//Reset 3/7
pwm.setPWM(7,0,map(vert+up+off[7],180,0,SERVOMIN, SERVOMAX));//Up
delay(dcnt);
pwm.setPWM(3,0,map(55+off[3],0,180,SERVOMIN, SERVOMAX));//reset forward
//Leave up
for (int cnt = 1; cnt <6; cnt++){
  pwm.setPWM(0,0,map(50+cnt+off[0],0,180,SERVOMIN, SERVOMAX));
  pwm.setPWM(1,0,map(45-cnt+off[1],180,0,SERVOMIN, SERVOMAX));
  pwm.setPWM(2,0,map(35+cnt+off[2],180,0,SERVOMIN, SERVOMAX));
  //pwm.setPWM(3,0,map(55-cnt+off[3],0,180,SERVOMIN, SERVOMAX)); //Reseting
  delay(dcnt);
}
  pwm.setPWM(7,0,map(vert+off[7],180,0,SERVOMIN, SERVOMAX));//Down
  delay(dcnt);

//Loop 4
//Start
//0 55+ //Resetting
//1 40-
//2 40+
//3 55-
//Reset 0/4
pwm.setPWM(4,0,map(vert+up+off[4],180,0,SERVOMIN, SERVOMAX));//Up
delay(dcnt);
pwm.setPWM(0,0,map(35+off[0],0,180,SERVOMIN, SERVOMAX)); //Reseting
//Leave up
for (int cnt = 1; cnt <6; cnt++){
  //pwm.setPWM(0,0,map(55+cnt+off[0],0,180,SERVOMIN, SERVOMAX)); //Resetting
  pwm.setPWM(1,0,map(40-cnt+off[1],180,0,SERVOMIN, SERVOMAX));
  pwm.setPWM(2,0,map(40+cnt+off[2],180,0,SERVOMIN, SERVOMAX));
  pwm.setPWM(3,0,map(55-cnt+off[3],0,180,SERVOMIN, SERVOMAX)); 
  delay(dcnt);
}
pwm.setPWM(4,0,map(vert+off[4],180,0,SERVOMIN, SERVOMAX));//Down
delay(dcnt);

//Loop 5
//Start
//0 35+
//1 35-//resetting
//2 45+
//3 50-
//Reset 1/5
pwm.setPWM(5,0,map(vert+up+off[5],0,180,SERVOMIN, SERVOMAX));//up
delay(dcnt);
pwm.setPWM(1,0,map(55+off[1],180,0,SERVOMIN, SERVOMAX));//Resetting
//Leave up
for (int cnt = 1; cnt <6; cnt++){
  pwm.setPWM(0,0,map(35+cnt+off[0],0,180,SERVOMIN, SERVOMAX));
  //pwm.setPWM(1,0,map(35-cnt+off[1],180,0,SERVOMIN, SERVOMAX));//Resetting
  pwm.setPWM(2,0,map(45+cnt+off[2],180,0,SERVOMIN, SERVOMAX));
  pwm.setPWM(3,0,map(50-cnt+off[3],0,180,SERVOMIN, SERVOMAX)); 
  delay(dcnt);
}
pwm.setPWM(5,0,map(vert+off[5],0,180,SERVOMIN, SERVOMAX));//down
delay(dcnt);

//End
//0 40
//1 55 //reset
//2 50
//3 45

}
