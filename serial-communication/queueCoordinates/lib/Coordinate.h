#ifndef Coordinate_h
#define Coordinate_h

#include "Arduino.h"

class Coordinate {
  public:
    static int xsign, ysign;
    static int x0, y0;

    int x, y;
    Coordinate(int x, int y);
};

Coordinate::Coordinate(int newX, int newY) {
    x = xsign * (newX + x0);
    y = ysign * (newY + y0);
}

#endif
