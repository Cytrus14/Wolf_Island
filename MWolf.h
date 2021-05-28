#pragma once
#include "FWolf.h"

class MWolf : public FWolf 
{
	int reproduceTimer = wolfReproductionTimerValue; //Male wolfs will try to reproduce only if reproduceTimer is equal to or less than 0
public:
	MWolf();
	void reproduceTimerReduce();
	void tryToReproduce(FWolf fWolfStorrageArray[], MWolf mWolfStorrageArray[], IslandClass& fWolfIsland, IslandClass& mWolfIsland, int* mWolfsAlive, int* allMWolfs, int* mWolfStartID, int* fWolfsAlive, int* allFWolfs, int* fWolfStartID, int islandSizeSq);
};