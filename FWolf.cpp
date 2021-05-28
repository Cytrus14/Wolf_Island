#include "FWolf.h"

FWolf::FWolf()
{
	isAlive = false;
}
void FWolf::create(IslandClass& entityIsland, int ID, int x, int y)
{
	fat = wolfStartFatValue;
	this->ID = ID;
	isAlive = true;
	entityIsland.setField(2, x, y);
	pos.x = x;
	pos.y = y;
}

void FWolf::burnCalories(IslandClass& fWolfIslnad, int* fWolfsAlive)
{
	fat -= 0.1;
	if (fat < 0)
		this->kill(fWolfIslnad, fWolfsAlive);
}

void FWolf::hunt(IslandClass& rabbitIsland, IslandClass& fWolfIsland, Rabbit rabbitStorageArray[], int* rabbitsAlive, int islandSizeSq)
{
	int i, j;
	int amountOfRabbitsNearby = 0;
	position rabbitsNearby[8];
	if (rabbitIsland.getField(pos.x, pos.y) == 2) { //checking whether a rabbit is on the same field
		for (i = 0; i < islandSizeSq; i++)
			if (rabbitStorageArray[i].pos.x == pos.x && rabbitStorageArray[i].pos.y == pos.y) {
				rabbitStorageArray[i].kill(rabbitIsland, rabbitsAlive);
				if (fat < wolfMaxFatValue)
					fat += wolfFatPerRabbitValue;
				if (fat > wolfMaxFatValue)
					fat = wolfMaxFatValue;
				return;
			}
	}

	for(i = pos.y - 1; i <= pos.y + 1; i++) //searching for rabbits on adjacent fields
		for(j = pos.x - 1; j <= pos.x + 1; j++ )
			if (rabbitIsland.getField(j, i) == 2 && fWolfIsland.getField(j, i) == 0) {
				rabbitsNearby[amountOfRabbitsNearby].x = j;
				rabbitsNearby[amountOfRabbitsNearby].y = i;
				amountOfRabbitsNearby++;
			}
	if (amountOfRabbitsNearby > 0) { //eating and killing prey
		int randomValue = rand() % amountOfRabbitsNearby;
		fWolfIsland.setField(0, pos.x, pos.y);
		pos.x = rabbitsNearby[randomValue].x;
		pos.y = rabbitsNearby[randomValue].y;
		fWolfIsland.setField(2, pos.x, pos.y);
		for (i = 0; i < islandSizeSq; i++)
			if (rabbitStorageArray[i].pos.x == pos.x && rabbitStorageArray[i].pos.y == pos.y) 
			{
				rabbitStorageArray[i].kill(rabbitIsland, rabbitsAlive);
				if(fat < wolfMaxFatValue)
					fat += wolfFatPerRabbitValue;
				if (fat > wolfMaxFatValue)
					fat = wolfMaxFatValue;
				return;
			}
	}
}


