#include "Plant.h"
#include "Entity.h"
#include <tuple>
        
using std::tuple;

Plant::Plant(tuple<int, int> coords, int growthRequired, int careRequired) : Entity(growthRequired, careRequired) {
    position = coords;
    watered = false;
}
void Plant::setPosition(tuple<int, int> coords) {
    position = coords;
}
tuple<int, int> Plant::getPosistion() const {
    return position;
} 

void Plant::waterPlant() {
    watered = true;
}
void Plant::dryPlant() {
    watered = false;
}
bool Plant::isWatered() {
    return watered;
}
