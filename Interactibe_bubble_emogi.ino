/* ----------------------------------------------------------------
  Author : Hak Se Engineer
  Date : 24/02/2023
  license status : open source
------------------------------------------------------------------*/

// need to add these header files using manage library option in the arduino IDE.
#include <ezButton.h> 
#include <Servo.h>

Servo myservo[2];
#define VRX_PIN  A7 // Arduino Nano pin connected to VRX pin
#define VRY_PIN  A6 // Arduino Nano pin connected to VRY pin
#define SW_PIN   12  // Arduino Nano pin connected to SW pin


ezButton button(SW_PIN);

int value_X = 0; // The variable to store value of the X axis
int value_Y = 0; // The variable to store value of the Y axis
int prev_value_X = 0;  //required to make smooth transition
int prev_value_Y = 0;  //required to make smooth transition

void setup() {

  myservo[0].attach(9);  //servo motor connected to Arduino pin 9
  myservo[1].attach(6);  //servo motor connected to Arduino pin 6
  
 // Serial.begin(9600) ;
}

void loop() {
  button.loop(); // MUST call the loop() function first
  
  // read analog X and Y analog values
  value_X = map (analogRead(VRX_PIN), 0, 1023, 0, 180);  //mapping joystick value with servo angle 
  value_Y = map (analogRead(VRY_PIN), 0, 1023, 0, 180);

  //For debug purpose...
  /*
  Serial.print("x = ");
  Serial.print(value_X);
  Serial.print(", y = ");
  Serial.println(value_Y);
  */
  
  if((value_X > prev_value_X +3)||(value_X < prev_value_X -3))
  {
        myservo[0].write(value_X); 
        prev_value_X = value_X;
  }
  if((value_Y > prev_value_Y +3)||(value_Y < prev_value_Y -3))
  {
        myservo[1].write(value_Y); 
        prev_value_Y = value_Y;
  }
  delay(50);

}
