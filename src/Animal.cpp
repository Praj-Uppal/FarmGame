#include "Animal.h"

coord Animal::getPosition() const
{
	return position;
}

void Animal::setPosition(coord value)
{
	position = value;
}