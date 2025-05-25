#include "Cow.h"

#include "Item.h"

// Define constructor for cow takes 5 days of growth and 1 day of care
Cow::Cow(coord position) : Animal(5, 1, "Cow") {}

// Define raise function,
void Cow::raise() {
  // if Fed cared for days goes up, and cow is set back to unfed
  if (isFed() == true) {
    setCaredForDays(getCaredForDays() + 1);
    unfeed();
  }
  // If cared days is greater than care required, cow grows and cared for days
  // is set back to 0
  if (getCaredForDays() >= getCareRequired()) {
    setGrowthStage(getGrowthStage() + 1);
    setCaredForDays(0);
  }
}

vector<tuple<Item*, int>> Cow::Slaughter() {
	//Define produce vector
  vector<tuple<Item*, int>> produce;
  if (isMature()) {
	//if mature, produce steak and push to vector
    Item* steak = new Item(10, 5, "Steak");
    produce.push_back(make_tuple(steak, 2));
    return produce;
  }
  // return empty vector if not harvestable
  return produce;
}
