#ifndef PLOT_H
#define PLOT_H
#include "Allincludes.h"

/**
 * The plot is a general-purpose container for game world entities. It provides
 * spatial management, which entails (x,y) coordinates of its top left corner,
 * and dimensions of length and height. It also defines common functions to add
 * or remove entities. Additionally, it includes common attributes such as
 * count, and capacity which will be relevant to all plots. It acts as a
 * container which ensures organised placement and updating of entities over
 * time.
 */
class Plot {
 private:
  // Define Attributes
  int currentCapacity;
  int maxCapacity;
  coord topLeftCoord;
  coord dimensions;

 public:
  // Declare Constructor and Destructor
  Plot() = delete;
  Plot(coord topLeft, coord dimension);

  // Declare get methods
  int getCurrentCapacity() const;
  int getMaxCapacity() const;
  coord getTopLeftCoord() const;
  coord getDimensions() const;

  // Declare set methods
  void setCurrentCapacity(int cap);
  void setMaxCapacity(int cap);
};

#endif
