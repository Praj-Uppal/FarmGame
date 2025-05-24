#ifndef FARMPLOT_H
#define FARMPLOT_H
#include <vector>

// #include "Allincludes.h"
#include "Plant.h"
#include "Plot.h"

using std::vector;

class FarmPlot : public Plot {
 protected:
 //Define vector of plants to store plants in a farmPlot
  vector<Plant*> plants;

 public:
  //Decalre constructors
  FarmPlot(coord topLeft, coord dimension);
  FarmPlot();

  //Declare functions
  bool addPlant(Plant* plant);
  bool removePlant(int index);
  vector<Plant*> getPlants();

  //Declare destructor
  // ~FarmPlot();
};

#endif
