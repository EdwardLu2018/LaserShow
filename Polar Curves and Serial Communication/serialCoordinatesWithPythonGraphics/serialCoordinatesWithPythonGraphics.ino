#include <Servo.h>
#include <math.h>

int incomingPts[2];

Servo xservo; // xaxis
Servo yservo; // yaxis

int time = 500;

int x0 = 95;
int y0 = 90;

int xsign = -1;
int ysign = 1;

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
        int xpos1 = xsign * incomingPts[i] + x0;
        Serial.print(incomingPts[i]);
        Serial.print(", ");
      }
      else {
        incomingPts[i] = Serial.read() - 11;
        int ypos1 = ysign * incomingPts[i] + y0;
        Serial.println(incomingPts[i]);
      }
    }
    xservo.write(xpos1);
    yservo.write(ypos1);
    delay(time);
  }
}
