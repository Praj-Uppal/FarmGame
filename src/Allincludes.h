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
#include "Plot.h"
#include "Plant.h"
#include "PotatoPlant.h"
#include "CarrotPlant.h"
#include "FarmPlot.h"
#include "Player.h"
#include "Shop.h"
#include "Display.h"


// Defining a type for coordinate
typedef tuple<int, int> coord;

// Defining Item attributes. Item(Sell Price, Buy price, Name)
//Also creating a pointer pointing to that specific item.
Item Carrotitem = Item(2,1,"Carrot");
Item* Carrot = &Carrotitem;

Item Potatoitem = Item(4,2,"Potato");
Item* Potato = &Potatoitem;

// Animals will need to have 2 items, one that is produced when
// harvested, and one which is used to create entity. For entity item make
// sure buy price and sell price are same to prevent infinite money glitches
Item cowCattleitem = Item(5, 5, "Cattle");
Item* cattle = &cowCattleitem;
// Cant purchase steak from shop so no point to Buyprice
Item Steakitem = Item(10, 10, "Steak");
Item* Steak = &Steakitem;

#endif