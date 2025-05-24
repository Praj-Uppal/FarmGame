#include "Plant.h"

#include <tuple>

#include "Entity.h"

using std::tuple;

Plant::Plant(tuple<int, int> coords, int growthRequired, int careRequired, string name) {
  this->careRequired = careRequired;
  this->growthRequired = growthRequired;
  growthStage = 0;
  caredForDays = 0;
  position = coords;
  watered = false;
  this->name = name;
}
void Plant::setPosition(tuple<int, int> coords) { position = coords; }
tuple<int, int> Plant::getPosistion() const { return position; }

void Plant::waterPlant() { watered = true; }
void Plant::dryPlant() { watered = false; }
bool Plant::isWatered() { return watered; }
