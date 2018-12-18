#include <Servo.h>
#include <math.h>
Servo xservo;  // xaxis servo object
Servo yservo;  // yaxis servo object

int xcoor[] = { -4, 0, 4, 3, -3};
int ycoor[] = { -3, 5, -3, -1, -1};
int arraySize = 5;
int Time = 150;
int x0 = 90;
int y0 = 93;
int ysign = 1;
int xsign = -1;

void setup()
{
  xservo.attach(9);    // attaches the servo on pin 9  to the servo object
  yservo.attach(10);   // attaches the servo on pin 10 to the servo object

  Serial.begin(9600);
  while (!Serial);
}

void loop()
{
  if (Serial.available())
  {
    int x = Serial.parseInt();
    int y = Serial.parseInt();
    Serial.println(x);
    Serial.println(y);
    for (int i = 0; i < arraySize; i++) {
      int x1pos = (xsign) * xcoor[i] + x0;
      int y1pos = (ysign) * ycoor[i] + y0;
      xservo.write(x1pos);
      yservo.write(y1pos);
      delay(Time);
    }
  }
}
