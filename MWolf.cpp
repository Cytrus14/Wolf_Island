#include "MWolf.h"

MWolf::MWolf()
{
	isAlive = false;
}

void MWolf::reproduceTimerReduce() 
{
	if (reproduceTimer > 0)
	{
		reproduceTimer--;
	}
}

void MWolf::tryToReproduce(FWolf fWolfStorrageArray[], MWolf mWolfStorrageArray[], IslandClass& fWolfIsland, IslandClass& mWolfIsland, int* mWolfsAlive, int* allMWolfs, int* mWolfStartID, int* fWolfsAlive, int* allFWolfs, int* fWolfStartID, int islandSizeSq)
{
	if (reproduceTimer <= 0 && ((*mWolfsAlive) < islandSizeSq || (*fWolfsAlive) < islandSizeSq))
	{
		int i, j, x, y, randomValue;
		int amountOfFWolfsNearby = 0;
		int amountOfAvailableFWolfsNearby = 0;
		int fWolfAbove = 0;
		int gender = -1; //offspring gender 0 - female,  1 - male
		int possibleFOffspringPositionsAmount = 0; //amount of possible positions for female offspring 
		int possibleMOffspringPositionsAmount = 0; //amount of possible positions for male offspring 
		position possibleFOffspringPositionsArray[8]; //array used for storing all possible female offspirng positions
		position possibleMOffspringPositionsArray[8]; //array used for storing all possible male offspirng positions
		position fWolfsNearby[8];
		position availableFWolfsNearby[8];

		if (fWolfIsland.getField(pos.x, pos.y) == 2) //checking whether a female wolf is on the same field
		{
			fWolfAbove++;
		}
		if (fWolfAbove == 0) 
		{
			for (i = pos.y - 1; i <= pos.y + 1; i++)  //searching for female wolfs around
				for (j = pos.x - 1; j <= pos.x + 1; j++)
					if (fWolfIsland.getField(j, i) == 2) {
						fWolfsNearby[amountOfFWolfsNearby].x = j;
						fWolfsNearby[amountOfFWolfsNearby].y = i;
						amountOfFWolfsNearby++;
					}
			j = 0;
			for (i = 0; i < amountOfFWolfsNearby; i++) { //checking which female wolfs nearby are free
				x = fWolfsNearby[i].x;
				y = fWolfsNearby[i].y;
				if (mWolfIsland.getField(x, y) == 0) {
					availableFWolfsNearby[j].x = x;
					availableFWolfsNearby[j].y = y;
					amountOfAvailableFWolfsNearby++;
					j++;
				}
			}
			if (amountOfAvailableFWolfsNearby > 0) { //moving to a random female wolf nearby
				randomValue = rand() % amountOfAvailableFWolfsNearby;
				mWolfIsland.setField(0, pos.x, pos.y);
				pos.x = availableFWolfsNearby[randomValue].x;
				pos.y = availableFWolfsNearby[randomValue].y;
				mWolfIsland.setField(2, pos.x, pos.y);
			}
		}

		if (amountOfAvailableFWolfsNearby > 0 || fWolfAbove > 0) //gathering possible offsping positions
		{
			for (i = pos.y - 1; i <= pos.y + 1; i++)
				for (j = pos.x - 1; j <= pos.x + 1; j++)
					if (fWolfIsland.getField(j, i) == 0) {
						possibleFOffspringPositionsArray[possibleFOffspringPositionsAmount].x = j;
						possibleFOffspringPositionsArray[possibleFOffspringPositionsAmount].y = i;
						possibleFOffspringPositionsAmount++;
					}
			for (i = pos.y - 1; i <= pos.y + 1; i++)
				for (j = pos.x - 1; j <= pos.x + 1; j++)
					if (mWolfIsland.getField(j, i) == 0) {
						possibleMOffspringPositionsArray[possibleMOffspringPositionsAmount].x = j;
						possibleMOffspringPositionsArray[possibleMOffspringPositionsAmount].y = i;
						possibleMOffspringPositionsAmount++;
					}
		}

		//choosing a gender for the offspring
		if (possibleFOffspringPositionsAmount > 0 && possibleMOffspringPositionsAmount > 0) 
		{
			randomValue = rand() % 2;
			gender = randomValue;
		}
		if (possibleFOffspringPositionsAmount > 0 && possibleMOffspringPositionsAmount == 0) 
		{
			gender = 0;
		}
		if (possibleFOffspringPositionsAmount == 0 && possibleMOffspringPositionsAmount > 0)
		{
			gender = 1;
		}

		//creating a female wolf on an adjacent field
		if (gender == 0)
		{
			randomValue = rand() % possibleFOffspringPositionsAmount;
			(*allFWolfs)++;
			(*fWolfsAlive)++;
			(*fWolfStartID)++;
			fWolfStorrageArray[*fWolfStartID-1].create(fWolfIsland, *allFWolfs, possibleFOffspringPositionsArray[randomValue].x, possibleFOffspringPositionsArray[randomValue].y); 
			reproduceTimer = wolfReproductionTimerValue;
			return;
		}
		//creating a male wolf on an adjacent field
		if (gender == 1)
		{
			randomValue = rand() % possibleMOffspringPositionsAmount;
			(*allMWolfs)++;
			(*mWolfsAlive)++;
			(*mWolfStartID)++;
			mWolfStorrageArray[*mWolfStartID-1].create(mWolfIsland, *allMWolfs, possibleMOffspringPositionsArray[randomValue].x, possibleMOffspringPositionsArray[randomValue].y);
			reproduceTimer = wolfReproductionTimerValue;
			return;
		}
	}
}
