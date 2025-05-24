#ifndef ENTITY_H
#define ENTITY_H
#include"Allincludes.h"
using namespace std;
class Entity {
    protected:
        int growthStage;
        int growthRequired;

        int caredForDays;
        int careRequired;

        string name;

    public:
        Entity(int growthRequired, int careRequired);

        // Get information regarding the entity
        bool isMature() const;
        int getGrowthStage();
        int getMaxGrowth();
        int getCaredForDays();
        int getCareRequired();
        // Set information
        void setCaredForDays(int days);
        void setGrowthStage(int stage);


        // Advance day functionality may vary by child class
        virtual void advanceDay() = 0;
};
#endif
