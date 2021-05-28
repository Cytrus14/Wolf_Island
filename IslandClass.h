#pragma once

class IslandClass
{
	int** entityMatrix;
	int islandSize = 40;
	int islandSizePlusOcean = islandSize + 10;
	bool isInitiated = false;
public:
	~IslandClass();
	void initiateEntityMatrix(int n);
	void clearEntityMatrix();
	void printEntityMatrix(); //this function is for debbuing purposes only
	void clearHedge();
	void setField(int value, int x, int y);
	int getField(int x, int y);
};


