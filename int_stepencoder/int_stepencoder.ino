#include <Arduino.h>

// -----------------------------------------------------------------------------
// constants

const int                                 PinCLK   = 2;     // Used for generating interrupts using CLK signal
const int                                 PinDT    = 3;     // Used for reading DT signal 4
const int                                 PinSW    = 4;     // Used for the push button switch 8

// -----------------------------------------------------------------------------
// global vars

volatile int                             virtualPosition    = 0;
volatile unsigned char result;

const unsigned char ttable[7][4] = {
{0x0, 0x2, 0x4, 0x0}, {0x3, 0x0, 0x1, 0x10},
{0x3, 0x2, 0x0, 0x0}, {0x3, 0x2, 0x1, 0x0},
{0x6, 0x0, 0x4, 0x0}, {0x6, 0x5, 0x0, 0x20},
{0x6, 0x5, 0x4, 0x0},
};

#define DIR_CCW 0x02
#define DIR_CW 0x03
volatile unsigned char state = 0;
volatile unsigned char pinstate;

// -----------------------------------------------------------------------------
// forward decls

void isr();
void loop();
void setup();

// -----------------------------------------------------------------------------
// Interrupt service routine is executed when a HIGH to LOW transition is detected on CLK

void isr ()  {
   pinstate = digitalRead(PinDT);
    state = ttable[state & 0xf][pinstate];
    //result=state&0x30;
    if(state==DIR_CCW)  virtualPosition = virtualPosition + 1;;
        if(state==DIR_CW)  virtualPosition = virtualPosition - 1;;
 //Serial.println(virtualPosition);
  // Serial.println(state);
  /*
    if (!digitalRead(PinDT))
        virtualPosition = virtualPosition + 1;
    else
        virtualPosition = virtualPosition - 1;
        */
    } // isr

// -----------------------------------------------------------------------------

void setup() {
    Serial.begin(9600);

    pinMode(PinCLK,INPUT);
    pinMode(PinDT, INPUT);
    pinMode(PinSW, INPUT);

    attachInterrupt(0, isr, FALLING);   // interrupt 0 is always connected to pin 2 on Arduino UNO

    Serial.println("Start");

    } // setup

// -----------------------------------------------------------------------------

void loop() {

    int                                    lastCount = 0;

    while (true) {
       /* if (!(digitalRead(PinSW))) {        // check if pushbutton is pressed
            virtualPosition = 0;            // if YES, then reset counter to ZERO
            while (!digitalRead(PinSW)) {}  // wait til switch is released
            delay(10);                      // debounce
            Serial.println("Reset");        // Using the word RESET instead of COUNT here to find out a buggy encoder
            }*/
        //if (virtualPosition != lastCount) {
           // lastCount = virtualPosition;
            //Serial.print("Count = ");
            //Serial.println(virtualPosition);
          //  }
        } // while
    } //loop
