#ifndef POTATOPLANT_H
#define POTATOPLANT_H

#include "Item.h"
#include "Plant.h"
#include <vector>

class PotatoPlant : public Plant {

    public:
        PotatoPlant(tuple<int, int> position);
        void advanceDay();
        vector<tuple<Item*,int>> harvest();
};

#endif
