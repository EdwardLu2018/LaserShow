#ifndef Coordinate_h
#define Coordinate_h

#include "Arduino.h"

class Coordinate {
  public:
    Coordinate(int x, int y);
    ~Coordinate();
    int x;
    int y;
};

Coordinate::Coordinate(int newX, int newY) {
    x = newX;
    x = newY;
}

#endif
