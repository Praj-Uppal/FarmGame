#include "Plot.h"

// Defining Constructor for Plot Class
Plot::Plot(coord topLeft, coord dimension)
    : currentCapacity(0),
      topLeftCoord(topLeft),
      // Max capacity is calculated by subtracting 2 from each dimension and
      // multiplying
      maxCapacity((get<0>(dimension) - 2) * (get<1>(dimension) - 2)),
      dimensions(dimension) {};

// Set methods for capacity
void Plot::setCurrentCapacity(int cap) { currentCapacity = cap; }
void Plot::setMaxCapacity(int cap) { maxCapacity = cap; }

// Get Methods for plot attributes
int Plot::getCurrentCapacity() const { return currentCapacity; }
int Plot::getMaxCapacity() const { return maxCapacity; }
coord Plot::getTopLeftCoord() const { return topLeftCoord; }
coord Plot::getDimensions() const { return dimensions; }
