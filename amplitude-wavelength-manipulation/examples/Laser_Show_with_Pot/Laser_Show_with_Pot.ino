#include <Servo.h>
Servo xservo;  // xaxis servo object
Servo yservo;  // yaxis servo object

int xsensorPinAmp = 0; // analog pin for manipulating amplitude for x position
int ysensorPinAmp = 1; // analog pin for manipulating amplitude for y position
int xsensorPinFreq = 2; // analog pin for manipulating frequency for x position
int ysensorPinFreq = 3; // analog pin for manipulating frequency for y position

int x0 = 90;  // variable stores x initial position
int y0 = 90;  // variable stores y initial position

int xcount;    // variable to store the x increment
int ycount;    // variable to store the y increment

int xpos;    // variable to store the x servo position
int ypos;    // variable to store the y servo position

int xamplitude;  //variable stores the max sweep of the servo - maximum value is 180
int yamplitude;  //variable stores the max sweep of the servo - maximum value is 180

int xcenter; //center of travel for the servo
int ycenter;

float xfreq;
float yfreq;

float xangle;
float yangle;

const double amplitudeConverter = 30.0 / 1023.0;

void setup()
{
  xservo.attach(9);    // attaches the servo on pin 9  to the servo object
  yservo.attach(10);   // attaches the servo on pin 10 to the servo object

  xcenter = x0 + xamplitude / 2;
  ycenter = y0 + yamplitude / 2;

  Serial.begin(9600);
  Serial.println("online...");
}

void loop()
{
  int xsensorValueAmp = analogRead(xsensorPinAmp); // from 0 to 1023
  int ysensorValueAmp = analogRead(ysensorPinAmp); // from 0 to 1023

  xamplitude = (int)(xsensorValueAmp * amplitudeConverter);
  yamplitude = (int)(ysensorValueAmp * amplitudeConverter); 

  int xsensorValueFreq = analogRead(xsensorPinFreq); // from 0 to 1023
  int ysensorValueFreq = analogRead(ysensorPinFreq); // from 0 to 1023

  xfreq = 180 - 360.0 / (int)(xsensorValueFreq / 30); // 360 / (sensor / 30) 
  yfreq = 180 - 360.0 / (int)(ysensorValueFreq / 30);

  xcount++; //increment x counter
  ycount++; //increment y counter

  xangle = (( (int)(xfreq * xcount) % 360) / 360.0) * 2 * PI; 
  yangle = (( (int)(yfreq * ycount) % 360) / 360.0) * 2 * PI; 

  xpos = int((xamplitude * (sin(xangle))) / 2 + xcenter); // A*sin((freq * t % 360) / 360) / 2 + k
  ypos = int((yamplitude * (cos(yangle))) / 2 + ycenter); 

  xservo.write(xpos);
  yservo.write(ypos);
  delay(250);


  Serial.println("xamp: \tyamp: \txfreq: \tyfreq: \txangle: \tyangle: ");
  Serial.print(xamplitude);
  Serial.print("\t");
  Serial.print(yamplitude);
  Serial.print("\t");
  Serial.print(xfreq);
  Serial.print("\t");
  Serial.print(yfreq);
  Serial.print("\t");
  Serial.print(xangle);
  Serial.print("\t\t");
  Serial.println(yangle);

//  Serial.print("(");
//  Serial.print(xpos);
//  Serial.print(",");
//  Serial.print(ypos);
//  Serial.println(")");
}

