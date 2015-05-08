//From bildr article: http://bildr.org/2012/08/rotary-encoder-arduino/
//From  http://tronixlabs.com/news/tutorial-l298n-dual-motor-controller-module-2a-and-arduino///
//Modified and programmed to the need from Dr Süleyman CANAN suleymancanan.wordpress.com
//these pins can not be changed 2/3 are special pins
int encoderPin1 = 2;
int encoderPin2 = 3;
int PinSW    = 4; 

int enA = 10;
int in1 = 9;
int in2 = 8;
int limUP = A0;
int limDW = A1;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;
volatile int counts;
unsigned char toggle=0;
 int start = 0;
     int stp = 0;
     int homestatus=0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

void setup() {
  Serial.begin (9600);

  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);
  
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(PinSW,INPUT);
  pinMode(limUP,INPUT);
  pinMode(limDW,INPUT);

  //digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  //digitalWrite(encoderPin2, HIGH); //turn pullup resistor on
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);
   //digitalWrite(in1, LOW);
   //digitalWrite(in2, HIGH);
    

}

void loop(){ 
  //Do stuff here

/*
if(counts<=0)
{
  counts=0;
  lastEncoded=0;
}
*/
if(counts>=255)
{
  counts=255;
  lastEncoded=0;
}

if (!(digitalRead(PinSW)))
{        // check if pushbutton is pressed
            toggle^=1;
           /* if(toggle==1){
                digitalWrite(in1, LOW);
                digitalWrite(in2, HIGH); 
            }
            if(toggle==0){
                digitalWrite(in1, HIGH);
                digitalWrite(in2, LOW); 
            }
*/
}  
while (!digitalRead(PinSW)) {}  // wait til switch is released
            delay(10);
if(homestatus==0)
demo();
if(homestatus)
{
gotoHome();//homestate();
counts=0;
}

limitUP();
limitDW();
//if(!stp)

///Serial.println(encoderValue/4);
Serial.println(counts);
//Serial.println(stp);
//Serial.println(toggle);
  //delay(1000); //just here to slow down the output, and show it will work  even during a delay
}

void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) //CCW
  {
    encoderValue --;
    if(encoderValue<=0) encoderValue=0;
  }
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)//CW
  {
   encoderValue++;
//   if(encoderValue>=255) encoderValue=255;
  }
  counts=(encoderValue/4)*5;
  lastEncoded = encoded; //store this value for next time
}
void limitDW()
{
  if(digitalRead(limDW))
  {
  digitalWrite(in1, LOW);// toward motor
  digitalWrite(in2, HIGH);
  analogWrite(enA, 100);
  delay(100);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
  homestatus=1;
  delay(1000);
  }
}
void limitUP()
{
  if(digitalRead(limUP))
  {
  digitalWrite(in1, HIGH);// toward the tail
  digitalWrite(in2, LOW);
  analogWrite(enA, 130);
  delay(250);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
  homestatus=0;
  counts=0;
//  delay(1000);
  }
}  

void gotoHome()
{
digitalWrite(in1, LOW);// toward motor
digitalWrite(in2, HIGH);
analogWrite(enA, 100);
}
  
void homestate()
{
//if(stp==0){
digitalWrite(in1, LOW);// toward motor
digitalWrite(in2, HIGH);
analogWrite(enA, 100);
while(digitalRead(limUP)==0){}
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
//}
delay(100);
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
analogWrite(enA, 0);
homestatus=0;
}


 void demo()
{
 if(toggle==1){
                digitalWrite(in1, LOW);
                digitalWrite(in2, HIGH); 
            }
            if(toggle==0){
                digitalWrite(in1, HIGH);
                digitalWrite(in2, LOW); 
            } 
  analogWrite(enA, counts);
  
 }
