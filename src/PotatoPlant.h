#ifndef POTATOPLANT_H
#define POTATOPLANT_H

#include "Item.h"
#include "Plant.h"
#include <vector>

class PotatoPlant : public Plant {

    public:
        //Declare constructor
        PotatoPlant(tuple<int, int> position);
        //Declare functions
        void advanceDay();
        vector<tuple<Item*,int>> harvest();
};

#endif
