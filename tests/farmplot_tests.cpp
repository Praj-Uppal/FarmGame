#include "CarrotPlant.h"
#include "FarmPlot.h"
void farmplot_constructor_test() {  // Check default constructor first
  FarmPlot f1 = FarmPlot();
  // Check top left
  if (f1.getTopLeftCoord() != coord(0, 0)) {
    cout << "Top left coord incorrect for default!" << endl;
    return;
  }
  // Check dimensions
  if (f1.getDimensions() != coord(20, 20)) {
    cout << "Default Dimensions incorrect!" << endl;
    return;
  }
  // Check max capacity
  if (f1.getMaxCapacity() != (18) * (18)) {
    cout << "Default max capacity is incorrect!" << endl;
    return;
  }
  // Check current capacity
  if (f1.getCurrentCapacity() != 0) {
    cout << "Default current capacity does not equal to 0." << endl;
  }
  // Create new farmplot with paramaters
  FarmPlot f2 = FarmPlot(coord(0, 1), coord(30, 30));
  // Check top left
  if (f2.getTopLeftCoord() != coord(0, 1)) {
    cout << "Top left coord incorrect for custom!" << endl;
    return;
  }
  // Check dimensions
  if (f2.getDimensions() != coord(30, 30)) {
    cout << "Custom dimensions incorrect!" << endl;
    return;
  }
  // Check max Capacity
  if (f2.getMaxCapacity() != (28) * (28)) {
    cout << "Custom Max capacity incorrect!" << endl;
    return;
  }
  // Check current capacity
  if (f2.getCurrentCapacity() != 0) {
    cout << "Custom Current Capacity incorrect!" << endl;
  }

  cout << "All constructor tests Passed!" << endl;
}

void farmplot_addplant_tests() {
  FarmPlot f1 = FarmPlot();
  Plant* p1 = new CarrotPlant(coord(3, 3));
  // Add plant to plot
  f1.addPlant(p1);
  // Check if capacity updated
  if (f1.getCurrentCapacity() != 1) {
    cout << "Farm Plot capacity is not 1!" << endl;
    return;
  }
  // Check if right plant was added!
  if (f1.getPlants().at(0)->getName() != "CarrotPlant") {
    cout << "Incorrect Plant in farm plot" << endl;
    return;
  }
  Plant* p2 = new CarrotPlant(coord(1, 1));
  f1.setCurrentCapacity(f1.getMaxCapacity());
  if (f1.addPlant(p2)) {
    cout << "Plant added beyond max capacity!" << endl;
  }
  cout << "All Add plants tests passed!" << endl;
}

void farmplot_removeplant_tests() {
  FarmPlot f1 = FarmPlot();
  Plant* p1 = new CarrotPlant(coord(3, 3));
  // Add plant to plot
  f1.addPlant(p1);
  // Attempt to remove plant
  if (!f1.removePlant(0)) {
    cout << "Plant removal failed!" << endl;
    return;
  }
  // Check new count
  if (f1.getCurrentCapacity() != 0) {
    cout << "Farm plot count did not go down!" << endl;
    return;
  }
  cout << "All remove plant tests passed!" << endl;
}

int main(void) {
  // Run tests
  farmplot_addplant_tests();
  farmplot_constructor_test();
  farmplot_removeplant_tests();
}