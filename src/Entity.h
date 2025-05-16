#ifndef ENTITY_H
#define ENTITY_H
#include <tuple>
using std::tuple;

class Entity {
    protected:
        int growthStage;
        int growthRequired;

        int caredForDays;
        int careRequired;

    public:
        Entity();
        virtual void advanceDay();
        bool isMature() const;
};
#endif
