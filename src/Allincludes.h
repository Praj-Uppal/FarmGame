#ifndef ALL_INCLUDES_H
#define ALL_INCLUDES_H

// Including All Header Files
#include <iostream>
#include <map>
#include <tuple>
#include <vector>

#include "Entity.h"
#include "Inventory.h"
#include "Item.h"
#include "Player.h"
#include "Plot.h"

// Defining a type for coordinate
typedef tuple<int, int> coord;

// Defining Item attributes. Item(Sell Price, Buy price, Name)
Item Carrot1 = Item(2,1,"Carrot");
Item* Carrot = &Carrot1;

Item Potato1 = Item(4,2,"Potato");
Item* Potato = &Potato1;

// Animals will need to have 2 items, one that is produced when
// harvested, and one which is used to create entity. For entity item make
// sure buy price and sell price are same to prevent infinite money glitches
Item cowCattle1 = Item(5, 5, "Cattle");
Item* cattle = &cowCattle1;
// Cant purchase steak from shop so no point to Buyprice
Item Steak1 = Item(10, 10, "Steak");
Item* Steak = &Steak1;

#endif