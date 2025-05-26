#ifndef ENTITY_H
#define ENTITY_H
#include "Allincludes.h"
using namespace std;
class Entity {
 protected:
  // Define attributes
  int growthStage;
  int growthRequired;

  int caredForDays;
  int careRequired;

  string name;

 public:
  // Get methods fpr the entity
  bool isMature() const;
  int getGrowthStage();
  int getMaxGrowth();
  int getCaredForDays();
  int getCareRequired();
  string getName();
  // Set methods for the entity
  void setCaredForDays(int days);
  void setGrowthStage(int stage);
  void setName(string name);

  // Advance day function must be implemented in the derived classes
  virtual void advanceDay() = 0;
};
#endif
