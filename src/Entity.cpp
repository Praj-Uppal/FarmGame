#include "Entity.h"

// Define is mature function
bool Entity::isMature() const {
  if (growthStage >= growthRequired) {
    return true;
  } else {
    return false;
  }
}

// Get methods for  the entity
int Entity::getGrowthStage() { return growthStage; }
int Entity::getMaxGrowth() { return growthRequired; }
int Entity::getCaredForDays() { return caredForDays; }
int Entity::getCareRequired() { return careRequired; }
string Entity::getName() { return name; }
// Set methods for the Entity (none needed for required variables as they are
// predefined by the constructors)
void Entity::setCaredForDays(int days) { caredForDays = days; }
void Entity::setGrowthStage(int stage) { growthStage = stage; }
void Entity::setName(string name) { this->name = name; }
