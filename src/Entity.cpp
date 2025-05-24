#include "Entity.h"


bool Entity::isMature() const {
    if (growthStage == growthRequired) {
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
void Entity::setCaredForDays(int days) {
    caredForDays = days;
}
void Entity::setGrowthStage(int stage) {
    growthStage = stage;
}
