const int STEP_PIN = 2;
const int Enable_PIN = 3;
const int DIR_PIN = 5;
void setup()
{
   pinMode(STEP_PIN, OUTPUT);
   pinMode(Enable_PIN, OUTPUT);
   pinMode(DIR_PIN, OUTPUT);
   digitalWrite(STEP_PIN, LOW);
   digitalWrite(Enable_PIN, HIGH); //When device turned on, stepper is off
   digitalWrite(DIR_PIN, HIGH);
   
} 
 
void loop()
{
         digitalWrite(Enable_PIN, LOW);
         digitalWrite(DIR_PIN, HIGH);
         int b=200;
 int a=10000;
   for (int i=0; i < 60000; i++)
      {
//        a=a-2;
        if (a<=b) a=b;
        else a=a-10;
        digitalWrite(STEP_PIN, HIGH);
         delayMicroseconds(10); 
         digitalWrite(STEP_PIN, LOW);
         //delay(a);
         delayMicroseconds(a); 
       }
       delay(1000);
}
 
