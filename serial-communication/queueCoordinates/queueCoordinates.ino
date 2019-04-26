#include <Servo.h>
#include <math.h>
#include "Coordinate.h"
#include "QueueArray.h"

Servo xservo; // xaxis
Servo yservo; // yaxis

int x0 = 90;
int y0 = 90;

QueueArray <Coordinate> coorQueue;

uint16_t incomingPts[2];

int xsign = -1;
int ysign = -1;

bool allDataReceived = false;

void setup () {
  Serial.begin(9600);
//  Serial.println("Starting...");
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
    if (incomingPts[0] != 244 && incomingPts[1] != 244) {
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
    xservo.write(currCoor.x);
    yservo.write(currCoor.y);
//    moveServo(xservo, 1000, currCoor.x);
//    moveServo(yservo, 1000, currCoor.y);
    Serial.print(currCoor.x);
    Serial.print(",");
    Serial.println(currCoor.y);
    coorQueue.enqueue(currCoor);
    delay(250);
  }
}

void moveServo(Servo ser, int milli, int pos) {
  double time = (double)milli / pos * 1000;
  for(int i = 0; i < pos; i++) {
    ser.write(i);
    delayMicroseconds(time);
  }
}
