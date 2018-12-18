#include <Servo.h>
Servo xservo;  // xaxis servo object
Servo yservo;  // yaxis servo object

int side = 10;
int xbegin = 130;  // variable stores y servo beginning position
int ybegin = 130;  // variable stores y servo beginning position
int xpos = xbegin - side;
int ypos = ybegin - side;


void setup()
{
  Serial.begin(9600);
  Serial.println("online...");
  xservo.attach(9);    // attaches the servo on pin 9  to the servo object
  yservo.attach(10);   // attaches the servo on pin 10 to the servo object

}

void loop()
{
  xservo.write(xbegin);
  yservo.write(ybegin);
  delay(200);
  xservo.write(xpos);
  delay(200);
  yservo.write(ypos);
  delay(200);
  xservo.write(xbegin);
  delay(200);
}
