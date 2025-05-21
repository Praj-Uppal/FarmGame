#ifndef FARMPLOT_H
#define FARMPLOT_H

#include "Plant.h"
#include "Plot.h"
#include <vector>

using std::vector;

class FarmPlot : protected Plot {
    protected:
        vector<Plant*> plants;
    public:
        FarmPlot();

        bool addPlant(Plant* plant);
        bool removePlant(int index);
        vector<Plant*> getPlants();

};

#endif
