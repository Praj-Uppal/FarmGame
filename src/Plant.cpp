#include "Plant.h"
#include "Entity.h"
#include <tuple>
        
using std::tuple;

Plant::Plant(tuple<int, int> coords, int growthRequired, int careRequired) : Entity(growthRequired, careRequired) {
    position = coords;
}
void Plant::setPosition(tuple<int, int> coords) {
    position = coords;
}
tuple<int, int> Plant::getPosistion() const {
    return position;
} 
