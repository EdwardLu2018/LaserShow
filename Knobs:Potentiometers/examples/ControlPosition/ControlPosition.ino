#include <Servo.h>
Servo xservo;  // xaxis servo object
Servo yservo;  // yaxis servo object

int xsensorPin = 0;
int ysensorPin = 1;

void setup() {
  xservo.attach(9);    // attaches the servo on pin 9  to the servo object
  yservo.attach(10);   // attaches the servo on pin 10 to the servo object

  Serial.begin(9600);
  Serial.println("online...");
}

void loop() {

  int xsensorValue;
  int ysensorValue;
  xsensorValue = analogRead(xsensorPin);
  ysensorValue = analogRead(ysensorPin);

  int xpos = (xsensorValue * 0.0880626223 + 45);
  int ypos = (ysensorValue * 0.0880626223 + 45);
  xservo.write(xpos);
  yservo.write(ypos);

  Serial.print("xposition = ");
  Serial.print(xpos);
  Serial.print("\t");
  Serial.print("yposition = ");
  Serial.print(ypos);
  Serial.println("\t");
}
