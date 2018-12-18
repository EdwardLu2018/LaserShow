#include <Servo.h>
#include <math.h>
#include "origin.h"

Servo xservo;  // xaxis servo object
Servo yservo;  // yaxis servo object
 
int time = 500;

int x0 = 85;
int y0 = 105;

int xsign = -1;
int ysign = -1;

void setup()
{
  xservo.attach(9);    // attaches the servo on pin 9  to the servo object
  yservo.attach(10);   // attaches the servo on pin 10 to the servo object

//  Serial.begin(9600);
//  while (!Serial);
//  Serial.println("online...");
}

void loop()
{
  for (int i = 0; i < numOfPoints; i++) {
      int xpos1 = xsign * coordinates[i][0] + x0;
      int ypos1 = ysign * coordinates[i][1] + y0;
      
//      Serial.print("(");
//      Serial.print(coordinates[i][0]);
//      Serial.print(",");
//      Serial.print(coordinates[i][1]);
//      Serial.println(")");
      
      xservo.write(xpos1);
      yservo.write(ypos1);
      delay(time);
  }
}
