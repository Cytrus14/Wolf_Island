#include "CustomHedgeMatrix.h"


CustomHedgeMatrix::~CustomHedgeMatrix()
{
	if (isInitiated)
	{
		for (int i = 0; i < n; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
	}
}
void CustomHedgeMatrix::printMatrix()
{
	for (int i = 0; i < n; i++) {
		std::cout << "\n";
		for (int j = 0; j < n; j++)
			std::cout << matrix[i][j] << " ";
	}
	std::cout << "\n";
}

void CustomHedgeMatrix::Initiate(int islandSize)
{
	n = islandSize;
	matrix = new int* [islandSize];
	for (int i = 0; i < islandSize; i++)
	{
		matrix[i] = new int[islandSize] {};
	}
	isInitiated = true;
}

int CustomHedgeMatrix::getField(int x, int y)
{
	if (x < n && y < n)
	{
		return matrix[y][x];
	}
	return 4;
}

void CustomHedgeMatrix::setField(int value, int x, int y)
{
	if (x < n && y < n && x >= 0 && y >= 0)
	{
		matrix[y][x] = value;
	}
}

int CustomHedgeMatrix::checkHedge()
{
	int amountOfHedgeTiles = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			if (matrix[i][j] == 3)
				amountOfHedgeTiles++;
	}
	return amountOfHedgeTiles;
}

void CustomHedgeMatrix::clearHedge()
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			matrix[i][j] = 0;
	}
}
