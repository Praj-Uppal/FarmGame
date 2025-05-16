#ifndef ENTITY_H
#define ENTITY_H

class Entity {
    protected:
        int growthStage;
        int growthRequired;

        int caredForDays;
        int careRequired;

    public:
        Entity(int growthRequired, int careRequired);

        bool isMature() const;
        int getGrowthStage();

        // Advance day functionality may vary by child class
        virtual void advanceDay() = 0;
};
#endif
