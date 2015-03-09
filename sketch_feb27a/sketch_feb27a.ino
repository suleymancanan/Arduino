const int STEP_PIN = 13;
const int Enable_PIN = 3;
const int DIR_PIN = 2;
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
   //Stop = digitalRead(Stop_PIN);
   //if (Stop == HIGH) {digitalWrite(Enable_PIN, HIGH);}
 
   //Forward = digitalRead(Forward_PIN);
   //if (Forward == HIGH) {digitalWrite(Enable_PIN, LOW);
      //digitalWrite(DIR_PIN, HIGH);}
 
   //Back = digitalRead(Back_PIN);
   //if (Back == HIGH) {digitalWrite(Enable_PIN, LOW);
      //digitalWrite(DIR_PIN, LOW);}
 
   //Origin = digitalRead(Origin_PIN);
   //if (Origin == HIGH)
      //{
        //  digitalWrite(Enable_PIN, LOW);
        //  digitalWrite(DIR_PIN, HIGH);
       //}
 
   //End = digitalRead(End_PIN);
   //if (End == HIGH)
     // {
         digitalWrite(Enable_PIN, LOW);
         digitalWrite(DIR_PIN, HIGH);
       //}
 
   //int Pin1 = digitalRead(Encoder_PIN_1);
   //int Pin2 = digitalRead(Encoder_PIN_2);
   //int Pin3 = digitalRead(Encoder_PIN_3);
   //int Pin4 = digitalRead(Encoder_PIN_4);
 
   //The following formula was empirically derived
   //If the dial is set to "zero" the lowest speed is 210 (interval between   pulses)
   //If the dial is set to "16" the highest speed is 60
   //RotationSpeed = 220 - (10 * (1 + ( (Pin1*8) + (Pin2*4) + (Pin3*2) + Pin4) ) ); 
 
//   RotationSpeed = 300; //use this line for testing and comment out the line above
 
   for (int i=0; i < 100; i++)
      {
         digitalWrite(STEP_PIN, HIGH);
         delayMicroseconds(5); 
         digitalWrite(STEP_PIN, LOW);
//         delayMicroseconds();
//         delay(1);
        delayMicroseconds(50); 
       }
}
 
