#include "FarmPlot.h"

#include "Plant.h"

//Define FarmPlot constructor
FarmPlot::FarmPlot(coord topLeft, coord dimension)
    : Plot(topLeft, dimension) {};

FarmPlot::FarmPlot() : Plot(coord(0, 0), coord(20, 20)) {};

// Function to add plant to a plot
bool FarmPlot::addPlant(Plant* plant) {
  // Check if plot is full
  if (getMaxCapacity() > getCurrentCapacity()) {
    //If not full add plant to vector and increment capacity
    setCurrentCapacity((getCurrentCapacity() + 1));
    plants.push_back(plant); //Plant pointer now in vector
    return true;
  } else {
    //If full return false
    return false;
  }
}

// Function to remove plant from a plot
bool FarmPlot::removePlant(int index) {
  if (index > getPlants().size()) {
    return false;
  } else {
    // Deallocate the memory for the plant
    delete plants[index];
    // Remove pointer from vector
    getPlants().erase(getPlants().begin() + index);
    return true;
  }
}
vector<Plant*> FarmPlot::getPlants() { return plants; }

// Destructor to deallocate memory for dynamically allocated plants
// FarmPlot::~FarmPlot() {
//   for (int i = 0; i < plants.size(); i++) {
//     delete plants.at(i);
//   }
//   //Clear vector
//   plants.clear();
// }
