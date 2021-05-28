#pragma once
#include "Entity.h"
#include "Rabbit.h"

class FWolf : public Entity
{
public:
	float fat = wolfStartFatValue;
	FWolf();
	void create(IslandClass& entityIsland, int ID, int x, int y)override;
	void burnCalories(IslandClass& fWolfIslnad, int* fWolfAlive);
	void hunt(IslandClass& rabbitIsland, IslandClass& fWolfIsland, Rabbit rabbitStorageArray[], int* rabbitsAlive, int islandSizeSq);
};

