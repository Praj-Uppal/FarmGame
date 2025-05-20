#ifndef FARMPLOT_H
#define FARMPLOT_H

#include "Plant.h"
#include "Plot.h"
#include <vector>

class FarmPlot : protected Plot {
    protected:
        std::vector<Plant*> plants;
    public:
        bool addPlant(Plant* plant);
        bool removePlant(tuple<int, int> position);
};

#endif
