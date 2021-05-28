#pragma once
#include <iostream>
#include <cstdlib> //random number generation
#include <ctime> //used for seeding the RNG
#include <SFML/graphics.hpp> //external graphics library
#include <windows.h> //used to access the windows sleep function
#include <random> //used for more advenced random number generation
#include <string>
#include "IslandClass.h"
#include "Rabbit.h"
#include "FWolf.h"
#include "MWolf.h"
#include "CustomHedgeMatrix.h"

class Simulation
{
    Rabbit* rabbitStorageArray;
    FWolf* fWolfStorrageArray;
    MWolf* mWolfStorrageArray;

    IslandClass rabbitIsland;
    IslandClass fWolfIsland;
    IslandClass mWolfIsland;

    bool whoHuntsFirst = false; // false - females, true - males
    bool isSimInitiated = false;

    int islandSize = 40;
    int islandSizeSq = islandSize * islandSize;

    void initiateEntityMatrixes(int isladSize);
public:
    bool isHedgeGenerated = false;

    //Creating an array for storing information about rabbits and the variables associated with it
    int rabbitsAlive = 0;
    int allRabits = 0;
    int rabbitStartID = 0;

    //Creating an array for storing information about female wolfs and the variables associated with it
    int fWolfsAlive = 0;
    int allFWolfs = 0;
    int fWolfStartID = 0;

    //Creating an array for storing information about male wolfs and the variables associated with it
    int mWolfsAlive = 0;
    int allMWolfs = 0;
    int mWolfStartID = 0;

    void addRabbit(int posX, int posY);
    void addFWolf(int posX, int posY);
    void addMWolf(int posX, int posY);
    void Start(int rabbits, int fWolfs, int mWolfs, int islandSize);
	void run(bool isHedgeEnabled, CustomHedgeMatrix& customHedge, bool& wasCustomHedgeModified);
    void draw(sf::RenderWindow& mainWindow, sf::RectangleShape& ocean, sf::RectangleShape& islandView, sf::RectangleShape& rabbitView, sf::CircleShape& fWolfView, sf::CircleShape& mWolfView, sf::Font& font1, bool isHedgeEnabled);
    ~Simulation();
};
