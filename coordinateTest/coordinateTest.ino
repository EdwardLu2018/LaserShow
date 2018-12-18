#include <Servo.h>
#include <math.h>
Servo xservo;  // xaxis servo object
Servo yservo;  // yaxis servo object

int x1 = 5;
int y1 = 5;
int x2 = 5;
int y2 = 0;
int x3 = 0;
int y3 = 5;
int x4 = 0;
int y4 = 0;
int lx = 1;
int ly = 7;


void setup()
{
  xservo.attach(9);    // attaches the servo on pin 9  to the servo object
  yservo.attach(10);   // attaches the servo on pin 10 to the servo object

  xservo.write(90);
  yservo.write(90);

  Serial.begin(9600);

  int x1pos = int((-((atan(x1 / (-lx)) * 180 / 3.14) - 90) / 2 ) + 45);
  int y1pos = int((-((atan(0 / (-ly)) * 180 / 3.14) - 90) / 2 ) + 45);
  Serial.println(y1pos);
  Serial.println(x1pos);
  xservo.write(x1pos);
  yservo.write(y1pos);
}

void loop()
{

}
