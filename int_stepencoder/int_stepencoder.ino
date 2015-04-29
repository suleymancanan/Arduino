#include <Arduino.h>
#include <AccelStepper.h>
// -----------------------------------------------------------------------------
// constants

const int                                 PinCLK   = 2;     // Used for generating interrupts using CLK signal
const int                                 PinDT    = 3;     // Used for reading DT signal 4
const int                                 PinSW    = 4;     // Used for the push button switch 8

// -----------------------------------------------------------------------------
// global vars

volatile long virtualPosition=0;
volatile unsigned char result;

const unsigned char ttable[7][4] = {
{0x0, 0x2, 0x4, 0x0}, {0x3, 0x0, 0x1, 0x10},
{0x3, 0x2, 0x0, 0x0}, {0x3, 0x2, 0x1, 0x0},
{0x6, 0x0, 0x4, 0x0}, {0x6, 0x5, 0x0, 0x20},
{0x6, 0x5, 0x4, 0x0},
};

#define DIR_CCW 0x02
#define DIR_CW 0x03
#define x1   A0
#define x10  A1
#define x100 A2

volatile unsigned char state = 0;
volatile unsigned char pinstate;
int motorStepPin = 8; //digital pin 3
int motorDirPin = 9; //digital pin 2
const int Enable_PIN = 10;
AccelStepper stepper(1, motorStepPin, motorDirPin);
int motorSpeed = 4000; //maximum steps per second (about 5rps / at 8 microsteps)
int motorAccel = 4000; //steps/second/second to accelerate
int multiplier=0,sw=0;

// -----------------------------------------------------------------------------
// forward decls

void isr();
void loop();
void setup();

// -----------------------------------------------------------------------------
// Interrupt service routine is executed when a HIGH to LOW transition is detected on CLK

void isr (){
   pinstate = digitalRead(PinDT);
    state = ttable[state & 0xf][pinstate];
    if(state==DIR_CCW)  virtualPosition = virtualPosition - multiplier;;
        if(state==DIR_CW)  virtualPosition = virtualPosition + multiplier;;
    }//isr

// -----------------------------------------------------------------------------

void setup() {
    Serial.begin(9600);

    pinMode(PinCLK,INPUT);
    pinMode(PinDT, INPUT);
    pinMode(PinSW, INPUT);
    pinMode(A0,INPUT);
    pinMode(A1,INPUT);
    pinMode(A2,INPUT);
  // pinMode(Enable_PIN, OUTPUT);
stepper.setEnablePin(10);
stepper.setPinsInverted(false,false,true);
stepper.setMinPulseWidth(20);
    
    stepper.setMaxSpeed(motorSpeed);
    stepper.setSpeed(motorSpeed);
    stepper.setAcceleration(motorAccel);
    
    //digitalWrite(Enable_PIN, LOW);
    attachInterrupt(0, isr, FALLING);   // interrupt 0 is always connected to pin 2 on Arduino UNO
    }

// -----------------------------------------------------------------------------

void loop() {

    int lastCount = 0;
    int toggle=0;
stepper.disableOutputs();
stepper.setCurrentPosition(0);
virtualPosition = 0;

    while (true) {
        if (!(digitalRead(PinSW))) {        // check if pushbutton is pressed
            stepper.setCurrentPosition(0);
            virtualPosition = 0;
            toggle^=1;
            if(toggle==1) stepper.enableOutputs(); 
            else stepper.disableOutputs();          // if YES, then reset counter to ZERO
            while (!digitalRead(PinSW)) {}  // wait til switch is released
            delay(10);                      // debounce
            }
            multiplier=1;
        //if(digitalRead(A0)) multiplier=1;
          //      if(digitalRead(A1)) multiplier=4;
            //            if(digitalRead(A2)) multiplier=16;
        
        if (virtualPosition != lastCount) {
            lastCount = virtualPosition;
            //stepper.moveTo(virtualPosition);
            //Serial.print("Count = ");
            Serial.println(virtualPosition);
           //Serial.println(stepper.currentPosition());
        }
             
             stepper.move(200);
                //stepper.moveTo(virtualPosition);
                // stepper.runSpeedToPosition();
                    stepper.run();
          

            
                                  
        } // while
    } //loop
