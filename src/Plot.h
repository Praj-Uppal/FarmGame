#ifndef PLOT_H
#define PLOT_H

#include <tuple>


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
     * 2D vector consisting of integers. The first
     */
    typedef std::tuple<int, int> IVec2;

public:
    Plot() = delete;
    virtual ~Plot() = default;

    inline int getCurrentCapacity() const
    {
        return currentCapacity;
    }

    inline int getMaxCapacity() const
    {
        return maxCapacity;
    }

    inline IVec2 getTopLeftCoord() const
    {
        return topLeftCoord;
    }

    inline IVec2 getDimensions() const
    {
        return dimensions;
    }
    void setCurrentCapacity(int cap);

private:
    int currentCapacity;
    int maxCapacity;
    IVec2 topLeftCoord;
    IVec2 dimensions;
};

#endif
