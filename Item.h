#ifndef ITEM_H
#define ITEM_H

#include <string.h>

#include <iostream>
using namespace std;

class Item {
 protected:
  // Define Item Attributes including sell cost, buy cost, if its plantable and
  // its name
  int sellCost, buyCost;
  bool plantable;
  string name;

 public:
  // Default and normal constructor
  Item(int sell, int buy, string name);
  Item();

  // Public Method to get variable values. Const to ensure they dont change
  // attribute values.
  int getSellCost() const;
  int getBuyCost() const;
  string getName() const;
  bool getPlantable() const;

  // Public Methods to set variable values.
  void setSellCost(int sell);
  void setBuyCost(int buy);
  void setName(string name);
  void setPlantable(bool status);
};

#endif