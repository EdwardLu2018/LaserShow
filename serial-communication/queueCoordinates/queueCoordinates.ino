#include <Servo.h>
#include <math.h>
#include "Coordinate.h"
#include "QueueArray.h"

Servo xservo; // xaxis
Servo yservo; // yaxis

int x0 = 95;
int y0 = 92;

QueueArray <Coordinate> coorQueue;

uint32_t incomingPts[2];

int xsign = -1;
int ysign = -1;

bool allDataReceived = false;

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
        incomingPts[i] = Serial.read() - 11;
    }
    if (incomingPts[0] != 99 && incomingPts[1] != 99) {
      coordinate.x = incomingPts[0] + x0;
      coordinate.y = incomingPts[1] + y0;
      coorQueue.enqueue(coordinate);
    }
    else {
      allDataReceived = true;
    }
  }

  if (allDataReceived) {
    Coordinate currCoor = coorQueue.dequeue();
  //  xservo.write(currCoor.x);
  //  yservo.write(currCoor.y);
    Serial.print(currCoor.x);
    Serial.print(",");
    Serial.println(currCoor.y);
    coorQueue.enqueue(currCoor);
  }
}
