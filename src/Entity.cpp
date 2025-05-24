#include "Entity.h"


bool Entity::isMature() const {
    if (growthStage >= growthRequired) {
        return true;
    } else {
        return false;
    }
}

int Entity::getGrowthStage() {
    return growthStage;
}
        // Get information regarding the entity
int Entity::getMaxGrowth() {
    return growthRequired;
}
int Entity::getCaredForDays() {
    return caredForDays;
}
int Entity::getCareRequired() {
    return careRequired;
}
string Entity::getName() {
    return name;
}
//Set methods for the Entity
void Entity::setCaredForDays(int days) {
    caredForDays = days;
}
void Entity::setGrowthStage(int stage) {
    growthStage = stage;
}
void Entity::setName(string name) {
    this->name = name;
}
