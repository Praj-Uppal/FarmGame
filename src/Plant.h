#ifndef PLANT_H
#define PLANT_H

#include "Entity.h"
#include "Item.h"
#include <tuple>
        
using std::tuple;

class Plant : protected Entity {
    protected:
        tuple<int, int> position;

    public:
        Plant(tuple<int, int> position, int growthRequired, int careRequired);
        void setPosition(tuple<int, int> pos);
        tuple<int, int> getPosistion() const;

        virtual void grow() = 0;
        virtual Item harvest() = 0;
};

#endif
