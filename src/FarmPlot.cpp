#include "FarmPlot.h"
#include "Plant.h"

// FarmPlot::FarmPlot() {

// }

FarmPlot::FarmPlot(int maxCap, coord topLeft, coord dimension): Plot(maxCap,topLeft,dimension) {};

FarmPlot::FarmPlot(): Plot(50,{0,0},{20,20}){};

bool FarmPlot::addPlant(Plant* plant) {
    if (getMaxCapacity() > getCurrentCapacity()) {
        setCurrentCapacity((getCurrentCapacity() + 1));
        plants.push_back(plant);
        return true;
    } else {
        return false;
    }
}

//Function to remove plant from a plot
bool FarmPlot::removePlant(int index) {
    
    if (index > getPlants().size()) {
        return false;
    } else {
        //Deallocate the memory for the plant
        delete plants[index];
        //Remove pointer from vector
        getPlants().erase(getPlants().begin() + index);
        return true;
    }
}
vector<Plant*> FarmPlot::getPlants() {
    return plants;
}

//Destructor to deallocate memory for dynamically allocated plants
FarmPlot::~FarmPlot(){
    for (int i = 0; i<plants.size(); i++) {
        delete plants.at(i);
    }
    plants.clear();
}