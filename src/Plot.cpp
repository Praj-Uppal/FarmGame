#include "Plot.h"

void Plot::setCurrentCapacity(int cap) { currentCapacity = cap; }

Plot::Plot(int maxCap, coord topLeft, coord dimension)
    : currentCapacity(0),
      maxCapacity(maxCap),
      topLeftCoord(topLeft),
      dimensions(dimension) {};
