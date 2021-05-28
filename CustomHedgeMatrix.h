#pragma once
#include <iostream>
class CustomHedgeMatrix
{
	int** matrix;
	int n;
	bool isInitiated = false;
public:
	~CustomHedgeMatrix();
	void printMatrix();
	void Initiate(int islandSize);
	int getField(int x, int y);
	void setField(int value, int x, int y);
	int checkHedge();
	void clearHedge();
};

