#ifndef PLANT_H
#define PLANT_H

#include "Entity.h"
#include "Item.h"
#include <tuple>
#include <vector>
        
using std::tuple;

class Plant : public Entity {
    protected:
        tuple<int, int> position;
        bool watered;

    public:
    //Declare constructor and destructor
        Plant(tuple<int, int> position, int growthRequired, int careRequired,string name);
        virtual ~Plant() = default;

        // Positional data
        void setPosition(tuple<int, int> pos);
        tuple<int, int> getPosistion() const;

        // water plant and check if it is watered
        void waterPlant();
        void dryPlant();
        bool isWatered();

        // Functions to be filled by child classes
        virtual void advanceDay() = 0;
        virtual vector<tuple<Item*,int>> harvest() = 0;
};

#endif
