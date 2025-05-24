#ifndef ANIMAL_H
#define ANIMAL_H

#include "Allincludes.h"
#include "Entity.h"

class Item;

/**
 * Analogous to the Plant class, the Animal class manages the life cycle and evolution of livestock. It
 * expands on the behaviours provided by the entity class and contains attributes such as the animal’s
 * growth stage, feeding status, and slaughtering status. The Animal class tracks and controls the animals
 * progress which depends on if they have been fed. Once an animal is fully raised, it can be slaughtered,
 * which returns a corresponding item into the player’s inventory, or used for reproduction (this is a future
 * feature and is not planned for the initial release but may be implemented if time permits).
 */
class Animal : public Entity
{
public:
	Animal(int growthRequired, int careRequired);
	virtual ~Animal() = default;

	// Virtual function which has to be implemented in the individual animals classes as
	// different animals have different evolution requirements
	virtual void raise() = 0;

	// Harvests animal and adds to user’s inventory, removes itself from Penn animals array.
	// As the type of item added to the users inventory, the quantity, and slaughter conditions 
	// vary, this is a virtual function 
	virtual class Item slaughter() = 0;

	coord getPosition() const;
	void setPosition(coord value);

private:
	coord position;
};

#endif