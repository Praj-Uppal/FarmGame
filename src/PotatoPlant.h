#ifndef POTATOPLANT_H
#define POTATOPLANT_H

#include "Item.h"
#include "Plant.h"
#include <vector>

class PotatoPlant : protected Plant {

    public:
        PotatoPlant(tuple<int, int> position);
        void advanceDay();
        vector<tuple<Item,int>> harvest();
};

#endif
