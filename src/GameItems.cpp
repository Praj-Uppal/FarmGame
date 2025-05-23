#include"Allincludes.h"
#include"Item.h"

// Defining Item attributes. Item(Sell Price, Buy price, Name)
//Also creating a pointer pointing to that specific item.
Item* Carrotitem = new Item(2,1,"Carrot");


Item* Potatoitem = new Item(4,2,"Potato");


// Animals will need to have 2 items, one that is produced when
// harvested, and one which is used to create entity. For entity item make
// sure buy price and sell price are same to prevent infinite money glitches
Item* cowCattleitem = new Item(5, 5, "Cattle");

// Cant purchase steak from shop so no point to Buyprice
Item* Steakitem = new Item(10, 10, "Steak");
