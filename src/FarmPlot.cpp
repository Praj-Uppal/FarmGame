#include "FarmPlot.h"
#include "Plant.h"

// FarmPlot::FarmPlot() {

// }

bool FarmPlot::addPlant(Plant* plant) {
    if (getMaxCapacity() > getCurrentCapacity()) {
        setCurrentCapacity((getCurrentCapacity() + 1));
        plants.push_back(plant);
        return true;
    } else {
        return false;
    }
}
bool FarmPlot::removePlant(int index) {
    
    if (index > getPlants().size()) {
        return false;
    } else {
        getPlants().erase(getPlants().begin() + index);
        return true;
    }
}
vector<Plant*> FarmPlot::getPlants() {
    return plants;
}
