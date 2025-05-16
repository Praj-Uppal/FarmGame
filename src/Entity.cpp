#include "Entity.h"

Entity::Entity(int care, int growth) {
    careRequired = care;
    growthRequired = growth;
    growthStage = 0;
    caredForDays = 0;
}

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
