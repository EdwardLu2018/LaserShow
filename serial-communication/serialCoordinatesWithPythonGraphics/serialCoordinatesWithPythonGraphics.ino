#include <Servo.h>
#include <math.h>

int incomingPts[2];

Servo xservo; // xaxis
Servo yservo; // yaxis

int t = 5;

int x0 = 95;
int y0 = 92;

int xpos;
int ypos;

int xsign = -1;
int ysign = -1;

void setup () {
  Serial.begin(9600);
  Serial.println("Starting...");
  
  xservo.attach(9);
  yservo.attach(10);
}

void loop () {
  while (Serial.available() >= 2) {
    for (int i = 0; i < 2; i++) {
      if (i == 0) {
        incomingPts[i] = Serial.read() - 11;
        xpos = xsign * incomingPts[i] + x0;
      }
      else {
        incomingPts[i] = Serial.read() - 11;
        ypos = ysign * incomingPts[i] + y0;
      }
    }
    xservo.write(xpos);
    yservo.write(ypos);
    //delay(t);
  }
}
