#define PinDT 3
#define CLK 2
//#define SW 4
#define DIR_CCW 0x02
#define DIR_CW 0x03

 unsigned char state = 0;
 unsigned char pinstate;

const unsigned char ttable[7][4] = {
{0x0, 0x2, 0x4, 0x0}, {0x3, 0x0, 0x1, 0x10},
{0x3, 0x2, 0x0, 0x0}, {0x3, 0x2, 0x1, 0x0},
{0x6, 0x0, 0x4, 0x0}, {0x6, 0x5, 0x0, 0x20},
{0x6, 0x5, 0x4, 0x0},
};

int counter=0,sw=0;
void isr();
void loop();
void setup();

void isr (){
    pinstate = digitalRead(PinDT);
    state = ttable[state & 0xf][pinstate];
    if(state==DIR_CCW)
    {
      counter--;
      if(counter<=0) counter=0;
    }
    if(state==DIR_CW)
    {
       counter++;
      if(counter>=255) counter=255;
    }
     delay(10);
} // isr

void setup(){
  Serial.begin(9600); 
  pinMode(PinDT, INPUT);   
  pinMode(CLK, INPUT);  
  //pinMode(SW, INPUT);
  attachInterrupt(0, isr, RISING);
}

void loop(){
// int counter;
// unsigned char result;
  /* Reset the counter */
 counter = 0;
 
  while(1)
  {
            //Serial.print("Count = ");
            Serial.println(counter);
//            Serial.print("State = ");
  //          Serial.println(state);
 
  }
}
