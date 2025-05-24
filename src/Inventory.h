#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>

#include "Item.h"

using namespace std;
class Inventory {
 protected:
  // Defining the map which will contain items. The key would be a string with
  // the name of the item which is pointing to a pair which contains an item and
  // its quantity. name -> (item pointer, quantity)
  map<string, pair<Item *, int>> inventoryMap;

 public:
  // Maps are automatically initialised and no other variables so default
  // constructor is only construcutor
  Inventory();
  //Declare destructor
  ~Inventory();

  // Methods to add or remove items from the inventory
  void addItem(Item *item, int Quantity);
  void addItem(Item *item);
  void removeItem(string itemName);
  void removeItem(string itemName, int Quantity);

  // Method to check how many of an item are contained in an inventory.
  int howMany(string name);

  // Method to print the inventory; mainly for testing.
  void printInventory();

  //Declare functions to provide begining and end of map so we can iterate 
  map<string,pair<Item*, int>>::iterator begin();
  map<string,pair<Item*,int>>::iterator end();
  map<string,pair<Item*, int>>::const_iterator begin() const;
  map<string,pair<Item*, int>>::const_iterator end() const;

  //Declare get and set method for inventory map
  map<string, pair<Item *, int>> getInventorymap() const;
  void setInventorymap(map<string, pair<Item *, int>> newmap);
};

#endif
