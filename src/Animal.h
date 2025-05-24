#ifndef ANIMAL_H
#define ANIMAL_H

#include "Allincludes.h"
#include "Entity.h"

class Item;

class Animal : public Entity
{
public:
	Animal() = default;
	virtual ~Animal() = default;

	// Virtual function which has to be implemented in the individual animals classes as
	// different animals have different evolution requirements
	virtual void raise() = 0;

	// Hrvests animal and adds to user’s inventory, removes itself from Penn animals array.
	// As the type of item added to the users inventory, the quantity, and slaughter conditions 
	// vary, this is a virtual function 
	virtual class Item slaughter() = 0;

	coord getPosition() const;
	void setPosition(coord value);

private:
	coord position;
};

#endif