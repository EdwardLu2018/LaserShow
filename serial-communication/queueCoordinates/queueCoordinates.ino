#include <Servo.h>
#include <math.h>
#include "Coordinate.h"
#include "QueueArray.h"

Servo xservo; // xaxis
Servo yservo; // yaxis

int x0 = 95;
int y0 = 92;

QueueArray <Coordinate> coorQueue;

int incomingPts[2];

int xsign = -1;
int ysign = -1;

void setup () {
  Serial.begin(9600);
  Serial.println("Starting...");
  coorQueue.setPrinter(Serial);

  xservo.attach(9);
  yservo.attach(10);
}

void loop () {
  while (Serial.available() >= 2) {
    Coordinate coordinate(0, 0);
    for (int i = 0; i < 2; i++) {
      if (i == 0) {
        incomingPts[i] = Serial.read() - 11;
        coordinate.x = xsign * incomingPts[i] + x0;
      }
      else {
        incomingPts[i] = Serial.read() - 11;
        coordinate.y = ysign * incomingPts[i] + y0;
      }
    }
    coorQueue.enqueue(coordinate);
  }

  while(!coorQueue.isEmpty()){
    Coordinate currCoor = coorQueue.dequeue();
  //  xservo.write(currCoor.x);
  //  yservo.write(currCoor.y);
    Serial.println(currCoor.x);
    Serial.println(currCoor.y);
    coorQueue.enqueue(currCoor);
  }
}
