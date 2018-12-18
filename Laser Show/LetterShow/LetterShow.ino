#include <Servo.h>
#include <math.h>
Servo xservo;  // xaxis servo object
Servo yservo;  // yaxis servo object

String letter;
int arraySize;
int Time = 120;
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

  Serial.println("online...");
}

void loop()
{

  if (Serial.available() > 0)
  {
    Time = Serial.parseInt();
    Serial.print("Delay is: ");
    Serial.print(Time);
    Serial.println(" millisecs");

    letter = Serial.readString();
    Serial.print("I will make a(n):");
    Serial.println(letter);
  }

  if (letter == ", a") {
    int xcoor[ ] = { -4, 0,  4,  3, -3 };
    int ycoor[ ] = { -3, 5, -3, -1, -1 };
    arraySize = 5;

    for (int i = 0; i < arraySize; i++)
    {
      int xpos = (xsign) * xcoor[i] + x0;
      int ypos = (ysign) * ycoor[i] + y0;
      xservo.write(xpos);
      yservo.write(ypos);
      delay(Time);
    }

  }

  else if (letter == ", b") {
    int xcoor[ ] = { -2, 2, 2, 1, -2, 1,  2,  2, -2 };
    int ycoor[ ] = {  4, 4, 1, 0,  0, 0, -1, -4, -4 };
    arraySize = 9;

    for (int i = 0; i < arraySize; i++)
    {
      int xpos = (xsign) * xcoor[i] + x0;
      int ypos = (ysign) * ycoor[i] + y0;
      xservo.write(xpos);
      yservo.write(ypos);
      delay(Time);
    }
  }

  else if (letter == ", c") {
    int xcoor[ ] = { 4, -3, -3, 4, -3, -3 };
    int ycoor[ ] = { 4, 4, -4, -4, -4,  4 };
    arraySize = 6;

    for (int i = 0; i < arraySize; i++)
    {
      int xpos = (xsign) * xcoor[i] + x0;
      int ypos = (ysign) * ycoor[i] + y0;
      xservo.write(xpos);
      yservo.write(ypos);
      delay(Time);
    }
  }

  else if (letter == ", d") {
    int xcoor[ ] = { -3, -3,  2,  3, 3, 2 };
    int ycoor[ ] = {  4, -3, -3, -2, 3, 4 };
    arraySize = 6;

    for (int i = 0; i < arraySize; i++)
    {
      int xpos = (xsign) * xcoor[i] + x0;
      int ypos = (ysign) * ycoor[i] + y0;
      xservo.write(xpos);
      yservo.write(ypos);
      delay(Time);
    }
  }

  else if (letter == ", e") {
    int xcoor[ ] = { 3, -2, -2, 2, -2, -3,  2, -3, -2 };
    int ycoor[ ] = { 4,  4,  0, 0,  0, -4, -4, -4, 4 };
    arraySize = 9;

    for (int i = 0; i < arraySize; i++)
    {
      int xpos = (xsign) * xcoor[i] + x0;
      int ypos = (ysign) * ycoor[i] + y0;
      xservo.write(xpos);
      yservo.write(ypos);
      delay(Time);
    }
  }

  else if (letter == ", f") {
    int xcoor[ ] = { 3, -2, -2, 2, -2, -3, -2 };
    int ycoor[ ] = { 4,  4,  0, 0,  0, -4, 4 };
    arraySize = 7;

    for (int i = 0; i < arraySize; i++)
    {
      int xpos = (xsign) * xcoor[i] + x0;
      int ypos = (ysign) * ycoor[i] + y0;
      xservo.write(xpos);
      yservo.write(ypos);
      delay(Time);
    }
  }

  else if (letter == ", g") {
    int xcoor[ ] = { 4, -3, -3,  4, 4, 1, 4,  4, -3, -3 };
    int ycoor[ ] = { 4,  4, -4, -4, 0, 0, 0, -4, -4, 4 };
    arraySize = 10;

    for (int i = 0; i < arraySize; i++)
    {
      int xpos = (xsign) * xcoor[i] + x0;
      int ypos = (ysign) * ycoor[i] + y0;
      xservo.write(xpos);
      yservo.write(ypos);
      delay(Time);
    }
  }

  else if (letter == ", h") {
    int xcoor[ ] = { 3,  3, 3, -3, -3, -3, -3, 3};
    int ycoor[ ] = { 4, -4, 0,  0,  4, -4, 0, 0 };
    arraySize = 8;

    for (int i = 0; i < arraySize; i++)
    {
      int xpos = (xsign) * xcoor[i] + x0;
      int ypos = (ysign) * ycoor[i] + y0;
      xservo.write(xpos);
      yservo.write(ypos);
      delay(Time);
    }
  }

  else if (letter == ", i") {
    int xcoor[ ] = { 0,  0 };
    int ycoor[ ] = { 4, -4 };
    arraySize = 2;

    for (int i = 0; i < arraySize; i++)
    {
      int xpos = (xsign) * xcoor[i] + x0;
      int ypos = (ysign) * ycoor[i] + y0;
      xservo.write(xpos);
      yservo.write(ypos);
      delay(Time);
    }
  }

  else if (letter == ", j") {
    int xcoor[ ] = { 0, -2, 2, 0, 0, -3, -3, -3,  0 };
    int ycoor[ ] = { 5,  5, 5, 5, -3, -3, 0, -3, -3, };
    arraySize = 9;

    for (int i = 0; i < arraySize; i++)
    {
      int xpos = (xsign) * xcoor[i] + x0;
      int ypos = (ysign) * ycoor[i] + y0;
      xservo.write(xpos);
      yservo.write(ypos);
      delay(Time);
    }
  }
}
