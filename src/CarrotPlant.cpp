#include "Allincludes.h"
#include "CarrotPlant.h"
#include "Plant.h"
#include <vector>

CarrotPlant::CarrotPlant(tuple<int, int> position) : Plant(position, 5, 2) {
    
}

vector<tuple<Item,int>> CarrotPlant::harvest() {
    vector<tuple<Item,int>> produce;
    if (isMature()) {
        produce.push_back({Carrotitem,2});
        return produce;
    }
    // return empty vector if not harvestable
    return produce;
}
void CarrotPlant::advanceDay() {
    // If the plant has been watered today, it has been cared for, the plant then dries out for the next day.
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
