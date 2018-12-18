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
int yoffset = 105;  // variable stores y servo offset position
int xcenter = 0; //center of travel for the servo
int ycenter = 0;
int xwavelength; // number of loops to complete one x cycle
int ywavelength; // number of loops to complete one y cycle
float xangle = 0; //current x angle goes from 0 to 2
float yangle = 0; //current x angle goes from 0 to 2

float waveConverter = 5.0 / 1023.0;

int xsensorValueAmp = 0;
int ysensorValueAmp = 0;

int xsensorValueWave = 0;
int ysensorValueWave = 0;

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

  xamplitude = map(xsensorValueAmp, 0, 1023, 1, 11);
  yamplitude = map(ysensorValueAmp, 0, 1023, 1, 11);
  xwavelength = (int)(xsensorValueWave * waveConverter) * 100 + 100;
  ywavelength = (int)(ysensorValueWave * waveConverter) * 100 + 100;

  if (xcount == xwavelength) xcount = 0; //reset xpos at the end of cycle
  if (ycount == ywavelength) ycount = 0; //reset ypos at the end of cycle

  xcount++; //increment x counter
  ycount++; //increment y counter

  xangle = (6.283 / float(xwavelength)) * xcount; // 2Pi rads in a circle
  yangle = (6.283 / float(ywavelength)) * ycount; // 2Pi rads in a circle

  xpos = int(xcenter + ((cos(xangle)) * xamplitude) / 2);
  ypos = int(ycenter + ((sin(yangle)) * yamplitude) / 2);

  xservo.write(xpos);
  yservo.write(ypos);

  //Serial.println("xamp:yamp:xwave:ywave");
  Serial.print(xamplitude);
  //Serial.print("\t");
  Serial.print(yamplitude);
  //Serial.print("\t");
  Serial.print(xwavelength);
  //Serial.print("\t");
  Serial.println(ywavelength);
}
