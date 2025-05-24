#include "Animal.h"

Animal::Animal(int growthRequired, int careRequired)
	: Entity(growthRequired, careRequired)
{	}

coord Animal::getPosition() const
{
	return position;
}

void Animal::setPosition(coord value)
{
	position = value;
}