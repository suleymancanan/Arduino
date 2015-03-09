//This is an example of how you would control 1 stepper

#include <AccelStepper.h>

//int motorSpeed = 9600; //maximum steps per second (about 3rps / at 16 microsteps)
int motorSpeed = 10000; //maximum steps per second (about 5rps / at 8 microsteps)
int motorAccel = 3600; //steps/second/second to accelerate
/*
int motorDirPin = 5; //digital pin 2
int motorStepPin = 2; //digital pin 3
const int Enable_PIN = 3;
*/

#define DT 2
#define CLK 3
#define SW 4
int motorStepPin = 8; //digital pin 3
int motorDirPin = 9; //digital pin 2
const int Enable_PIN = 10;

//set up the accelStepper intance
//the "1" tells it we are using a driver
AccelStepper stepper(1, motorStepPin, motorDirPin); 



void setup(){
  stepper.setMaxSpeed(motorSpeed);
  stepper.setSpeed(motorSpeed);
  stepper.setAcceleration(motorAccel);
  pinMode(Enable_PIN, OUTPUT);
  digitalWrite(Enable_PIN, LOW);
  stepper.moveTo(8000); //move 32000 steps (should be 10 rev)
  Serial.begin(9600); 
  pinMode(DT, INPUT);   
  pinMode(CLK, INPUT);  
  pinMode(SW, INPUT);  
  digitalWrite(SW, HIGH);
}

void loop(){
 int counter;
 byte DialPos;
 byte Last_DialPos;
  /* Reset the counter */
 counter = 0;
  //if stepper is at desired location
 /*
  if (stepper.distanceToGo() == 0){
    //go the other way the same amount of steps
    //so if current position is 400 steps out, go position -400
   stepper.moveTo(-stepper.currentPosition()); 
   //stepper.moveTo(-1600); 
  }
  */
  //these must be called as often as possible to ensure smooth operation
  //any delay will cause jerky motion
  
  while(1)
  {
    /* Read the status of the dial */
    DialPos = (digitalRead(CLK) << 1) | digitalRead(DT);
  
    /* Is the dial being turned anti-clockwise? */
    if (DialPos == 3 && Last_DialPos == 1)
    {
      counter--;
    }
  
    /* Is the dial being turned clockwise? */
    if (DialPos == 3 && Last_DialPos == 2)
    {
      counter++;
    }
  
    /* Output the counter to the serial port */
    //Serial.println(counter);
 
    /* Is the switch pressed? */
   // if(!digitalRead(SW))
     // Serial.println("Switch pressed!");
  
    /* Save the state of the encoder */
    Last_DialPos = DialPos;
    //stepper.moveTo(-stepper.currentPosition());
    stepper.moveTo(counter*200);
    stepper.run();
  }
}
