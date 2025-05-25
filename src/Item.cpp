#include "Item.h"

// Define constructor. First value is buy cost, followed by sell cost, and
// lastly the name of the item
Item::Item(int sell,int buy, string name)
    : sellCost(sell), buyCost(buy), name(name) {};
// Define Default; let buy cost = sell cost = 0, and name be blank;
Item::Item() : Item(0, 0, "") {};

// Define Get methods. Simply return the corresponding variable.
int Item::getBuyCost() const { return buyCost; }
int Item::getSellCost() const { return sellCost; }
string Item::getName() const { return name; }
bool Item::getPlantable() const { return plantable; }

// Define Set methods. Simply sets the corresponding variable to the provided
// value.
void Item::setBuyCost(int buy) { buyCost = buy; }
void Item::setSellCost(int sell) { sellCost = sell; }
void Item::setName(string name) { this->name = name; }
void Item::setPlantable(bool status) { plantable = status; }
