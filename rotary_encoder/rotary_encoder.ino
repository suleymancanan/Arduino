
/* FILE:    Rotary_Encoder_Example.cpp
   DATE:    17/07/14
   VERSION: 0.1
   AUTHOR:  Andrew Davies

This is basic example of how to read the thate of a rotary encoder such as the
KY=040 Rotary Encoder Module (HCMODU0063).

You may copy, alter and reuse this code in any way you like, but please leave
reference to HobbyComponents.com in your comments if you redistribute this code.
This software may not be used directly for the purpose of selling products that
directly compete with Hobby Components Ltd's own range of products.

THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS MAKES NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR LACK OF NEGLIGENCE.
HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR ANY DAMAGES,
INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY
REASON WHATSOEVER.
*/

/* Define digital pins used to read the encoder */
#define DT 2
#define CLK 3
#define SW 4


void setup()
{
  Serial.begin(9600); 
  pinMode(DT, INPUT);   
  pinMode(CLK, INPUT);  
  pinMode(SW, INPUT);  
  digitalWrite(SW, HIGH);
}

/* Main program */
void loop()
{
 int counter;
 byte DialPos;
 byte Last_DialPos;
 
 /* Reset the counter */
 counter = 0;
 
  /* Continiouously read the state of the encoder */
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
    Serial.println(counter);
 
    /* Is the switch pressed? */
    if(!digitalRead(SW))
      Serial.println("Switch pressed!");
  
    /* Save the state of the encoder */
    Last_DialPos = DialPos;
  }
}
