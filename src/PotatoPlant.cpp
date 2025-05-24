#include "PotatoPlant.h"
#include "Plant.h"
#include <vector>

PotatoPlant::PotatoPlant(tuple<int, int> position) : Plant(position, 7, 3) {
    
}

vector<tuple<Item*,int>> PotatoPlant::harvest() {
    vector<tuple<Item*,int>> produce;
    if (isMature()) {
        //Push back the "harvested" items, and thier quantity into a vector
        Item* Potato = new Item(4,2,"Potato");
        produce.push_back({Potato,4});
        return produce;
    }
    // return empty vector if not harvestable
    return produce;
}
void PotatoPlant::advanceDay() {
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
