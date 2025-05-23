#ifndef PLOT_H
#define PLOT_H
#include"Allincludes.h"


/**
 * The plot is a general-purpose container for game world entities. It provides spatial management, which
 * entails (x,y) coordinates of its top left corner, and dimensions of length and height. It also defines
 * common functions to add or remove entities. Additionally, it includes common attributes such as count,
 * and capacity which will be relevant to all plots. It acts as a container which ensures organised
 * placement and updating of entities over time.
 */
class Plot
{
    /**
     * Defining a pair consisting of integers.
     */

public:
    Plot() = delete;
    virtual ~Plot() = default;

    Plot(int maxCap, coord topLeft, coord dimension);

    inline int getCurrentCapacity() const
    {
        return currentCapacity;
    }

    inline int getMaxCapacity() const
    {
        return maxCapacity;
    }

    inline coord getTopLeftCoord() const
    {
        return topLeftCoord;
    }

    inline coord getDimensions() const
    {
        return dimensions;
    }
    void setCurrentCapacity(int cap);

private:
    int currentCapacity;
    int maxCapacity;
    coord topLeftCoord;
    coord dimensions;
};

#endif
