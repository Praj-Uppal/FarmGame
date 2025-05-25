#include "CarrotPlant.h"

void plant_constructor_test() {
  // Create plant
  Plant* p1 = new CarrotPlant(make_tuple(1, 1));

  if (p1->getPosistion() != make_tuple(1, 1)) {
    cout << "Plant position not initialised correctly! Plant is not at (1,1)";
    return;
  }
  if (p1->getCareRequired() != 1) {
    cout << "Plant care required is not 0!" << endl;
    return;
  }
  if (p1->getMaxGrowth() != 3) {
    cout << "Plant Growth required is not 0!" << endl;
    return;
  }
  if (p1->getGrowthStage() != 0) {
    cout << "Plant Growth Stage is not 0!" << endl;
    return;
  }
  if (p1->getCaredForDays() != 0) {
    cout << "Plant cared for days is not 0!" << endl;
    return;
  }
  if (p1->getName() != "CarrotPlant") {
    cout << "Plant name was not intialised properly!" << endl;
    return;
  }
  cout << "All plant constructor tests passed!" << endl;
  delete p1;
}

void plant_set_method_tests() {
  // Create plant
  Plant* p1 = new CarrotPlant(make_tuple(1, 1));
  // Use set methods
  p1->setCaredForDays(2);
  p1->setGrowthStage(1);
  p1->setName("Test plant2");
  p1->setPosition(make_tuple(0, 0));
  // Check if set methods worked
  if (p1->getCaredForDays() != 2) {
    cout << "Set method for cared days failed!" << endl;
    return;
  }
  if (p1->getGrowthStage() != 1) {
    cout << "Set method for growth stage failed!" << endl;
    return;
  }
  if (p1->getName() != "Test plant2") {
    cout << "Set method for name has failed!" << endl;
    return;
  }
  if (p1->getPosistion() != make_tuple(0, 0)) {
    cout << "Set method for position has failed!" << endl;
    return;
  }
  delete p1;
  cout << "All set methods functional! Tests passed!" << endl;
}

void plant_waterMethods_tests() {
  // Create plant
  Plant* p1 = new CarrotPlant(make_tuple(1, 1));
  // Water plant
  p1->waterPlant();
  // Check if watered
  if (!p1->isWatered()) {
    cout << "Watering plant test failed!" << endl;
    return;
  }
  // Dry plan
  p1->dryPlant();
  // Check if dried
  if (p1->isWatered()) {
    cout << "Drying Plant Test Failed!" << endl;
    return;
  }

  cout << "All Watering methods tests passed!" << endl;
  delete p1;
}

void plant_advanceDay_test() {
  // Create plant
  Plant* p1 = new CarrotPlant(make_tuple(1, 1));
  // Water plant
  p1->waterPlant();
  // call advance day
  p1->advanceDay();
  // Check
  if (p1->getCaredForDays() !=
      0) {  // 0 because it should progress in growth stage
    cout << "Plant cared for days is incorrect!" << endl;
    return;
  }
  if (p1->isWatered()) {
    cout << "Plant was not dried!" << endl;
    return;
  }
  // Also check if growth stage progressed
  if (p1->getGrowthStage() != 1) {
    cout << "Plant did not grow!" << endl;
    return;
  }

  cout << "All advance day tests passed!" << endl;
  delete p1;
}

void plant_harvest_test() {
  // Create plant
  Plant* p1 = new CarrotPlant(make_tuple(1, 1));
  vector<tuple<Item*, int>> result = p1->harvest();
  // Check if its not empty
  if (!result.empty()) {
    cout << "Harvest triggered incorrectly!" << endl;
    return;
  }
  // Make mature
  p1->setGrowthStage(3);
  // Call harvest
  result = p1->harvest();
  // Create Item
  Item* Carrot = new Item(2, 1, "Carrot");
  // Define expected result
  tuple<Item*, int> Expectedresult = make_tuple(Carrot, 2);
  // Check if actual result matches expected result;
  if (std::get<1>(result.at(0)) != std::get<1>(Expectedresult)) {
    cout << "Harvest results incorrect!" << endl;
    return;
  }
  cout << "All harvest tests passed!" << endl;
  // Delete
  delete Carrot;
  delete p1;
}

int main(void) {
  // Run Tests
  plant_constructor_test();
  plant_set_method_tests();
  plant_waterMethods_tests();
  plant_advanceDay_test();
  plant_harvest_test();
}
