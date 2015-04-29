#include <Arduino.h>
//#include <AccelStepper.h>
// -----------------------------------------------------------------------------
// constants

const int                                 PinCLK   = 2;     // Used for generating interrupts using CLK signal
const int                                 PinDT    = 3;     // Used for reading DT signal 4
//const int                                 PinSW    = 4;     // Used for the push button switch 8

// -----------------------------------------------------------------------------
// global vars

const unsigned char ttable[7][4] = {
  {0x0, 0x2, 0x4,  0x0}, {0x3, 0x0, 0x1, 0x10},
  {0x3, 0x2, 0x0,  0x0}, {0x3, 0x2, 0x1,  0x0},
  {0x6, 0x0, 0x4,  0x0}, {0x6, 0x5, 0x0, 0x10},
  {0x6, 0x5, 0x4,  0x0},
};


/*
const unsigned char ttable[7][4] = {
{0x0, 0x2, 0x4, 0x0}, {0x3, 0x0, 0x1, 0x10},
{0x3, 0x2, 0x0, 0x0}, {0x3, 0x2, 0x1, 0x0},
{0x6, 0x0, 0x4, 0x0}, {0x6, 0x5, 0x0, 0x20},
{0x6, 0x5, 0x4, 0x0},
};*/
/*
const unsigned char ttable[7][4] = {
  {0x0, 0x2, 0x4,  0x0}, {0x3, 0x0, 0x1, 0x10},
  {0x3, 0x2, 0x0,  0x0}, {0x3, 0x2, 0x1,  0x0},
  {0x6, 0x0, 0x4,  0x0}, {0x6, 0x5, 0x0, 0x10},
  {0x6, 0x5, 0x4,  0x0},
};
*/
/*
const unsigned char ttable[7][4] = {
  {0x0, 0x2, 0x4,  0x0}, {0x3, 0x0, 0x1, 0x40},
  {0x3, 0x2, 0x0,  0x0}, {0x3, 0x2, 0x1,  0x0},
  {0x6, 0x0, 0x4,  0x0}, {0x6, 0x5, 0x0, 0x80},
  {0x6, 0x5, 0x4,  0x0},
  };
  */
//#define DIR_CCW 0x10
//#define DIR_CW 0x20
#define DIR_CCW 2
#define DIR_CW 3


volatile unsigned char state = 1;
volatile unsigned char pinstate;
volatile unsigned char result;
int counter=0;


// -----------------------------------------------------------------------------
// forward decls

void isr();
void loop();
void setup();

// -----------------------------------------------------------------------------
// Interrupt service routine is executed when a HIGH to LOW transition is detected on CLK

void isr (){
  //unsigned char result;
/*  pinstate = (digitalRead(PinCLK) << 1) | digitalRead(PinDT);
    state = ttable[state & 0xf][pinstate];
    result=state;//&0xc0;
    //Serial.println(result);
    if(state==DIR_CCW) counter++;
    if(state==DIR_CW) counter--;
    */
 
  pinstate = (digitalRead(PinCLK) << 1) | digitalRead(PinDT);
  //pinstate = digitalRead(PinDT);
    state = ttable[state & 0xf][pinstate];
//    Serial.println(state);
    if(state==DIR_CW)  
    {
      
      counter++;
      if(counter>=255) counter=255;
    }
    
    if(state==DIR_CCW)
    {
       counter--;
       if(counter<=0) counter=0;
    }
        delay(10);
    }//isr

// -----------------------------------------------------------------------------

void setup() {
    Serial.begin(9600);

    pinMode(PinCLK,INPUT);
    pinMode(PinDT, INPUT);
  //  pinMode(PinSW, INPUT);
   digitalWrite(PinCLK, HIGH);
  digitalWrite(PinDT, HIGH);
  
  
    attachInterrupt(0, isr, FALLING);   // interrupt 0 is always connected to pin 2 on Arduino UNO
    }

// -----------------------------------------------------------------------------

void loop() {
   
    while (true) {
                 
            Serial.println(counter);
                        //Serial.println(result);
           //Serial.println(DIR_CCW); 
             //         Serial.println(DIR_CW); 
         
        
      } // while
    } //loop
