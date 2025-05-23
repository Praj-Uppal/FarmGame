#ifndef FARMPLOT_H
#define FARMPLOT_H
#include"Allincludes.h"
#include "Plant.h"
#include "Plot.h"
#include <vector>

using std::vector;

class FarmPlot : public Plot {
    protected:
        vector<Plant*> plants;
    public:
        FarmPlot(int maxCap, coord topLeft, coord dimension);
        FarmPlot();

        bool addPlant(Plant* plant);
        bool removePlant(int index);
        vector<Plant*> getPlants();

        ~FarmPlot();
};

#endif
