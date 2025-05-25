#include "CarrotPlant.h"

#include "Allincludes.h"

// Define Constructor. Carrot take 3 days to grow and 1 days to be cared for.
CarrotPlant::CarrotPlant(tuple<int, int> position)
    : Plant(position, 3, 1, "CarrotPlant") {};

vector<tuple<Item*, int>> CarrotPlant::harvest() {
  vector<tuple<Item*, int>> produce;
  if (isMature()) {
    Item* Carrot = new Item(2, 1, "Carrot");
    produce.push_back(make_tuple(Carrot, 2));
    return produce;
  }
  // return empty vector if not harvestable
  return produce;
}
void CarrotPlant::advanceDay() {
  // If the plant has been watered today, it has been cared for, the plant then
  // dries out for the next day.
  if (isWatered()) {
    setCaredForDays((getCaredForDays() + 1));
    dryPlant();
  }
  // When the plant grows, it requires care again.
  if (getCaredForDays() >= getCareRequired()) {
    setGrowthStage((getGrowthStage() + 1));
    setCaredForDays(0);
  }
}
