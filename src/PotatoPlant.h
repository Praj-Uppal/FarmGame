#ifndef POTATOPLANT_H
#define POTATOPLANT_H

#include <vector>

#include "Item.h"
#include "Plant.h"

class PotatoPlant : public Plant {
 public:
  // Declare constructor
  PotatoPlant(tuple<int, int> position);
  // Declare functions
  void advanceDay();
  vector<tuple<Item*, int>> harvest();
};

#endif
