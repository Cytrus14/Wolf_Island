#include "IslandClass.h"
#include "iostream"

void IslandClass::initiateEntityMatrix(int n)
{
	islandSize = n;
	islandSizePlusOcean = islandSize + 10;
	entityMatrix = new int*[islandSizePlusOcean];
	for (int i = 0; i < islandSizePlusOcean; i++)
	{
		entityMatrix[i] = new int[islandSizePlusOcean];
	}
	isInitiated = true;
}

IslandClass::~IslandClass()
{
	if (isInitiated)
	{
		for (int i = 0; i < islandSizePlusOcean; i++)
		{
			delete[] entityMatrix[i];
		}
		delete[] entityMatrix;
	}
}

void IslandClass::clearEntityMatrix()
{
	int i;
	int j;
	for(i = 0; i < islandSizePlusOcean; i++)
		for(j = 0; j < islandSizePlusOcean; j++)
			entityMatrix[i][j] = 1;
	for (i = 5; i < islandSize + 5; i++)
		for (j = 5; j < islandSize + 5; j++)
			entityMatrix[i][j] = 0;
}

void IslandClass::printEntityMatrix() 
{
	for (int i = 0; i < islandSizePlusOcean; i++) {
	std::cout << "\n";
	for (int j = 0; j < islandSizePlusOcean; j++)
		std::cout << entityMatrix[i][j]<<" ";
	}
}

void IslandClass::clearHedge()
{
	for (int i = 0; i < islandSizePlusOcean; i++)
		for (int j = 0; j < islandSizePlusOcean; j++)
			if(entityMatrix[i][j] == 3)
				entityMatrix[i][j] = 0;
}

void IslandClass::setField(int value, int x, int y)
{
	if (x < islandSizePlusOcean && y < islandSizePlusOcean)
	{
		entityMatrix[y][x] = value;
	}
}

int IslandClass::getField(int x, int y)
{
	if (x < islandSizePlusOcean && y < islandSizePlusOcean)
	{
		return entityMatrix[y][x];
	}
	return 4;
}