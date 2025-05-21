#ifndef CARROTPLANT_H
#define CARROTPLANT_H

#include "Item.h"
#include "Plant.h"
#include <vector>

class CarrotPlant : public Plant {

    public:
        CarrotPlant(tuple<int, int> position);
        void advanceDay();
        vector<tuple<Item,int>> harvest();
};

#endif
