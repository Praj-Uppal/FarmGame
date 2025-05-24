#include "Animal.h"

Animal::Animal(int _growthRequired, int _careRequired)
{	
	growthStage = 0;
	growthRequired = _growthRequired;

	caredForDays = 0;
	careRequired = _careRequired;
}

Animal::~Animal()
{	}

bool Animal::isMature() const
{
	return growthStage >= growthRequired;
}

coord Animal::getPosition() const
{
	return position;
}

void Animal::setPosition(coord value)
{
	position = value;
}