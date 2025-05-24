#ifndef ALL_INCLUDES_H
#define ALL_INCLUDES_H

// Including All Header Files
#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include<ncurses.h>

using namespace std;
// Defining a type for coordinate
typedef tuple<int, int> coord;


// Declare Item attributes. Item(Sell Price, Buy price, Name)
//Also Declaring a pointer pointing to that specific item.
#include"Item.h"
extern Item Carrotitem;
extern Item* Carrot;

extern Item Potatoitem;
extern Item* Potato;

// Animals will need to have 2 items, one that is produced when
// harvested, and one which is used to create entity. For entity item make
// sure buy price and sell price are same to prevent infinite money glitches
extern Item cowCattleitem;
extern Item* cattle;
// Cant purchase steak from shop so no point to Buyprice
extern Item Steakitem;
extern Item* Steak;

#endif
