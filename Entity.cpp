#include "Entity.h"

void Entity::create(IslandClass& entityIsland, int ID, int x, int y)
{
	this->ID = ID;
	isAlive = true;
	entityIsland.setField(2, x, y);
	pos.x = x;
	pos.y = y;
}

void Entity::kill(IslandClass& entityIsland, int* entitiesAlive)
{
	isAlive = false;
	entityIsland.setField(0, pos.x, pos.y);
	(*entitiesAlive)--;
}

void Entity::move(IslandClass& entityIsland)
{
	int i, j, randomValue;
	int possiblePositionsAmount = 0; //stores information about the amount of possible positions
	position possiblePositionsArray[8];

	randomValue = rand() % 9; //randomValue = 0 to 8, if randomValue = 0 the entity won't attempt to move
	if (randomValue == 0)
		return;

	for (i = pos.y - 1; i <= pos.y + 1; i++)	//gathers possible positions
		for (j = pos.x - 1; j <= pos.x + 1; j++)
			if (entityIsland.getField(j, i)== 0) 
			{
				possiblePositionsArray[possiblePositionsAmount].x = j;
				possiblePositionsArray[possiblePositionsAmount].y = i;
				possiblePositionsAmount++;
			}
	if (possiblePositionsAmount > 0)//selecting a new position and updating the entity matrix
	{	
		randomValue = rand() % possiblePositionsAmount;
		entityIsland.setField(0, pos.x, pos.y);
		pos.x = possiblePositionsArray[randomValue].x;
		pos.y = possiblePositionsArray[randomValue].y;
		entityIsland.setField(2, pos.x, pos.y);
	}
}
