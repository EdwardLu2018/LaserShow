#include <Servo.h>
Servo xservo;  // xaxis servo object
Servo yservo;  // yaxis servo object

int xsensorPinAmp = 0; // analog pin for manipulating amplitude for x position
int ysensorPinAmp = 1; // analog pin for manipulating amplitude for y position
int xsensorPinWave = 2; // analog pin for manipulating wavelength for x position
int ysensorPinWave = 3; // analog pin for manipulating wavelength for y position

int xcount = 0;    // variable to store the x increment
int ycount = 0;    // variable to store the y increment
int xpos = 0;    // variable to store the x servo position
int ypos = 0;    // variable to store the y servo position
int xamplitude;  //variable stores the max sweep of the servo - maximum value is 180
int yamplitude;  //variable stores the max sweep of the servo - maximum value is 180
int xoffset = 85;  // variable stores x servo offset position
int yoffset = 100;  // variable stores y servo offset position
int xcenter = 0; //center of travel for the servo
int ycenter = 0;
int xwavelength; // number of loops to complete one x cycle
int ywavelength; // number of loops to complete one y cycle
float xangle = 0; //current x angle goes from 0 to 2
float yangle = 0; //current x angle goes from 0 to 2

int xsensorValueAmp = 0;
int ysensorValueAmp = 0;

int xsensorValueWave = 0;
int ysensorValueWave = 0;

float theta = 0;
int a;
int b;

void setup()
{
  xservo.attach(9); // attaches the servo on pin 9  to the servo object
  yservo.attach(10); // attaches the servo on pin 10 to the servo object

  xcenter = xoffset + xamplitude / 2;
  ycenter = yoffset + yamplitude / 2;

  Serial.begin(9600);
  Serial.println("online...");
}

void loop()
{
  xsensorValueAmp = analogRead(xsensorPinAmp); // from 0 to 1023
  ysensorValueAmp = analogRead(ysensorPinAmp); // from 0 to 1023
  xsensorValueWave = analogRead(xsensorPinWave); // from 0 to 1023
  ysensorValueWave = analogRead(ysensorPinWave); // from 0 to 1023

  a = map(xsensorValueAmp, 0, 1023, 1, 11);
  b = map(ysensorValueAmp, 0, 1023, 1, 11);

  theta += 0.1;
  
  xpos = xcenter + int(0.5*cos(theta)*(a + b * sin(theta)));
  ypos = ycenter + int(0.5*sin(theta)*(a + b * sin(theta)));

  xservo.write(xpos);
  yservo.write(ypos);

  Serial.print("(");
  Serial.print(a);
  Serial.print(",");
  Serial.print(b);
  Serial.println(")");
  
}
