#pragma once
#include "IslandClass.h"
#include "Entity.h"

class Rabbit : public Entity
{
public:
	Rabbit();
	void tryToReproduce(Rabbit rabbitStorageArray[], IslandClass& rabbitIsland, int* rabbitsAlive, int* allRabbits, int* rabbitStartID, int islandSizeSq);
};