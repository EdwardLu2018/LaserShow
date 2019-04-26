#include <Servo.h>

Servo xservo; // xaxis
Servo yservo; // yaxis

int x0 = 95;
int y0 = 92;

int xpos;
int ypos;

int xsign = -1;
int ysign = -1;

uint16_t incomingPts[2];

void setup () {
  Serial.begin(9600);
  Serial.println("Starting...");
  
  xservo.attach(9);
  yservo.attach(10);
}

void loop () {
  while (Serial.available() >= 2) {
    for (int i = 0; i < 2; i++) {
      incomingPts[i] = Serial.read() - 11;
    }
    xpos = xsign * incomingPts[0] + x0;
    ypos = ysign * incomingPts[1] + y0;
    xservo.write(xpos);
    yservo.write(ypos);
  }
}
