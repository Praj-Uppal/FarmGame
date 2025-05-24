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
        // Get information regarding the entity
        bool isMature() const;
        int getGrowthStage();
        int getMaxGrowth();
        int getCaredForDays();
        int getCareRequired();
        string getName();
        // Set information
        void setCaredForDays(int days);
        void setGrowthStage(int stage);
        void setName(string name);


        // Advance day functionality may vary by child class
        virtual void advanceDay() = 0;
};
#endif
