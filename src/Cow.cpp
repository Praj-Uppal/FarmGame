#include "Cow.h"
#include "Item.h"

Cow::Cow(int growthRequired, int careRequired)
	: Animal(growthRequired, careRequired)
{	}

void Cow::raise()
{
	setCaredForDays(getCaredForDays() + 1);

	if(getCaredForDays() >= getCareRequired())
	{
		setGrowthStage(getGrowthStage() + 1);
		setCaredForDays(0);
	}
}

std::vector<Item*> Cow::slaughter()
{
	std::vector<Item*> produce;

	if(isMature())
	{
		for(int i = 0; i < 3; i++)
		{
			produce.push_back(new Item(8, 4, "Beef"));
		}
	}

	return produce;
}
