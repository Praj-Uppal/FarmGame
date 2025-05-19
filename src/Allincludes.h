#ifndef ALL_INCLUDES_H
#define ALL_INCLUDES_H

// Including All Header Files
#include <iostream>
#include <map>
#include <tuple>
#include<vector>
#include "Entity.h"
#include "Inventory.h"
#include "Item.h"
#include "Player.h"
#include "Plot.h"

// Defining a type for coordinate
typedef tuple<int, int> coord;

// Defining Item attributes. Item(Sell Price, Buy price, Name)
Item* Carrot = &Item(2, 1, "Carrot");
Item* Potato = &Item(4, 2, "Potato");

// Animals will need to have 2 items, one that is produced when
// harvested, and one which is used to create entity. For entity item make
// sure buy price and sell price are same to prevent infinite money glitches
Item* cowCattle = &Item(5, 5, "Cattle");
// Cant purchase steak from shop so point to Buyprice
Item* Steak = &Item(10, 10, "Steak");

#endif