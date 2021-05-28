#pragma once
#include <cstdlib>
#include "IslandClass.h"
#include "GlobalVariables.h"

struct position
{
	int x;
	int y;
};

class Entity
{
public:
	int ID;
	position pos;
	bool isAlive = false;
	void virtual create(IslandClass& entityIsland, int ID, int x, int y);
	void kill(IslandClass& entityIsland, int* entitiesAlive);
	void move(IslandClass& entityIsland);
};