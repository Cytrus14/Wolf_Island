#include <cstdlib>
#include "Rabbit.h"

Rabbit::Rabbit()
{
	isAlive = false;
}

void Rabbit::tryToReproduce(Rabbit rabbitStorageArray[], IslandClass& rabbitIsland, int* rabbitsAlive, int* allRabbits, int* rabbitStartID, int islandSizeSq)
{
	if (rabbitReproducitonFactorValue < 1)
		rabbitReproducitonFactorValue = 1; //correcting rabbitReproducitonFactorValue if it's less than 1
	int randomValue = rand() % rabbitReproducitonFactorValue;

	if (randomValue == 0 && ((*rabbitsAlive) < islandSizeSq)) {
		int i, j;
		int possiblePositionsAmount = 0; //amount of possible offspring postions
		position possiblePositionsArray[8];

		for (i = pos.y - 1; i <= pos.y + 1; i++)	//gathering possible offspring positions
			for (j = pos.x - 1; j <= pos.x + 1; j++)
				if (rabbitIsland.getField(j, i) == 0) {
					possiblePositionsArray[possiblePositionsAmount].x = j;
					possiblePositionsArray[possiblePositionsAmount].y = i;
					possiblePositionsAmount++;
				}

		if (possiblePositionsAmount > 0) {	//creating a new rabbit on an adjacent field and updating entity matrix
			randomValue = rand() % possiblePositionsAmount;
			(*allRabbits)++;
			(*rabbitsAlive)++;
			(*rabbitStartID)++;
			rabbitStorageArray[*rabbitStartID-1].create(rabbitIsland, *allRabbits, possiblePositionsArray[randomValue].x, possiblePositionsArray[randomValue].y);
		}

	}
}