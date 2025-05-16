#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include <map>

using namespace std;

class Inventory
{
protected:
    // Defining the map which will contain items. The key would be a string with the name of the item which is pointing to a pair which contains an item and its quantity.
    // name -> (item pointer, quantity)
    map<string, pair<Item *, int>> inventoryMap;

public:
    // Maps are automatically initialised and no other variables so defualt constructor is only construcutor
    Inventory();

    //Methods to add or remove items from the inventory 
    void addItem(Item *item, int Quantity);
    void removeItem(string itemName, int Quantity);

    //Method to check how many of an item are contained in an inventory.
    int howMany(string name);

    //Method to print the inventory; mainly for testing.
    void printInventory();
};

#endif