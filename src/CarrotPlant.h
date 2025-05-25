#ifndef CARROTPLANT_H
#define CARROTPLANT_H

#include "Item.h"
#include "Plant.h"
#include <vector>

class CarrotPlant : public Plant {
    public:
    //Declare constructor
        CarrotPlant(tuple<int, int> position);
        //Declare advance day functions and Harvest function
        void advanceDay();
        vector<tuple<Item*,int>> harvest();
};

#endif
