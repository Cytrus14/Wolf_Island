#include "Simulation.h"

void sortStorageArray(Rabbit StorageArray[], int* StartID, int islandSize);
void sortStorageArray(FWolf StorageArray[], int* StartID, int islandSize);
void sortStorageArray(MWolf StorageArray[], int* StartID, int islandSize);

void Simulation::initiateEntityMatrixes(int islandSize)
{
    rabbitIsland.initiateEntityMatrix(islandSize);
    fWolfIsland.initiateEntityMatrix(islandSize);
    mWolfIsland.initiateEntityMatrix(islandSize);
	rabbitIsland.clearEntityMatrix();
	fWolfIsland.clearEntityMatrix();
	mWolfIsland.clearEntityMatrix();
}

void Simulation::Start(int rabbits, int fWolfs, int mWolfs, int islandSize)
{
    this->islandSize = islandSize;
    islandSizeSq = islandSize * islandSize;

    //allocating memory for entity storage arrays
    rabbitStorageArray = new Rabbit[islandSizeSq];
    fWolfStorrageArray = new FWolf[islandSizeSq];
    mWolfStorrageArray = new MWolf[islandSizeSq];

    //initiating entity matrixes
    this->initiateEntityMatrixes(this->islandSize);

    int i = 0;
    int j = 0;

    rabbitsAlive = 0;
    allRabits = 0;
    rabbitStartID = 0;
    fWolfsAlive = 0;
    allFWolfs = 0;
    fWolfStartID = 0;
    mWolfsAlive = 0;
    allMWolfs = 0;
    mWolfStartID = 0;

    //setting up the RNG
    std::random_device rng;
    std::mt19937 gen(rng());
    std::uniform_int_distribution<> distr(5, islandSize + 4);

    position tempPosition;
    int generatedPositionsAmount = 0;
    bool duplication = false;

    //generating unique positions for rabbits and creating them
    position* generatedPositions = new position[rabbits];
    while (i < rabbits)
    {
        tempPosition.x = distr(gen);
        tempPosition.y = distr(gen);
        for(j = 0; j < generatedPositionsAmount; j++)
        {
            if (generatedPositions[j].x == tempPosition.x && generatedPositions[j].y == tempPosition.y)
            {
                duplication = true;
                break;
            }
        }
        if (!duplication)
        {
            generatedPositions[i] = tempPosition;
            generatedPositionsAmount++;
            i++;
        }
        duplication = false;
    }
    i = 0;
    generatedPositionsAmount = 0;
    while (i < rabbits)
    {
        rabbitStorageArray[i].create(rabbitIsland, rabbitStartID, generatedPositions[i].x, generatedPositions[i].y);
        rabbitsAlive++;
        allRabits++;
        rabbitStartID++;
        i++;
    }
    delete[] generatedPositions;
    i = 0;

    //generating unique positions for female wolfs and creating them
    generatedPositions = new position[fWolfs];
    while (i < fWolfs)
    {
        tempPosition.x = distr(gen);
        tempPosition.y = distr(gen);
        for (j = 0; j < generatedPositionsAmount; j++)
        {
            if (generatedPositions[j].x == tempPosition.x && generatedPositions[j].y == tempPosition.y)
            {
                duplication = true;
                break;
            }
        }
        if (!duplication)
        {
            generatedPositions[i] = tempPosition;
            generatedPositionsAmount++;
            i++;
        }
        duplication = false;
    }
    i = 0;
    generatedPositionsAmount = 0;
    while (i < fWolfs)
    {
        fWolfStorrageArray[i].create(fWolfIsland, fWolfStartID, generatedPositions[i].x, generatedPositions[i].y);
        fWolfsAlive++;
        allFWolfs++;
        fWolfStartID++;
        i++;
    }
    delete[] generatedPositions;
    i = 0;

    //generating unique positions for male wolfs and creating them
    generatedPositions = new position[mWolfs];
    while (i < mWolfs)
    {
        tempPosition.x = distr(gen);
        tempPosition.y = distr(gen);
        for (j = 0; j < generatedPositionsAmount; j++)
        {
            if (generatedPositions[j].x == tempPosition.x && generatedPositions[j].y == tempPosition.y)
            {
                duplication = true;
                break;
            }
        }
        if (!duplication)
        {
            generatedPositions[i] = tempPosition;
            generatedPositionsAmount++;
            i++;
        }
        duplication = false;
    }
    i = 0;
    while (i < mWolfs)
    {
        mWolfStorrageArray[i].create(mWolfIsland, mWolfStartID, generatedPositions[i].x, generatedPositions[i].y);
        mWolfsAlive++;
        allMWolfs++;
        mWolfStartID++;
        i++;
    }
    isSimInitiated = true;
    delete[] generatedPositions;
}
void Simulation::run(bool isHedgeEnabled, CustomHedgeMatrix& customHedge, bool& wasCustomHedgeModified)
{
    sortStorageArray(fWolfStorrageArray, &fWolfStartID, islandSize);
    sortStorageArray(mWolfStorrageArray, &mWolfStartID, islandSize);
    //rabbits move
    for (int i = 0; i < islandSizeSq; i++)
        if (rabbitStorageArray[i].isAlive)
            rabbitStorageArray[i].move(rabbitIsland);
    //rabbits try to reproduce
     for (int i = 0; i < islandSizeSq; i++)
         if (rabbitStorageArray[i].isAlive)
             rabbitStorageArray[i].tryToReproduce(rabbitStorageArray, rabbitIsland, &rabbitsAlive, &allRabits, &rabbitStartID, islandSizeSq);
     //wolfs try to reproduce
     for (int i = 0; i < islandSizeSq; i++)
         if (mWolfStorrageArray[i].isAlive)
             mWolfStorrageArray[i].tryToReproduce(fWolfStorrageArray, mWolfStorrageArray, fWolfIsland, mWolfIsland, &mWolfsAlive, &allMWolfs, &mWolfStartID, &fWolfsAlive, &allFWolfs, &fWolfStartID, islandSizeSq);
     //wolfs hunt
     if (!whoHuntsFirst)
     {
         for (int i = 0; i < islandSizeSq; i++)
             if (fWolfStorrageArray[i].isAlive)
                 fWolfStorrageArray[i].hunt(rabbitIsland, fWolfIsland, rabbitStorageArray, &rabbitsAlive, islandSizeSq);
         for (int i = 0; i < islandSizeSq; i++)
             if (mWolfStorrageArray[i].isAlive)
                 mWolfStorrageArray[i].hunt(rabbitIsland, mWolfIsland, rabbitStorageArray, &rabbitsAlive, islandSizeSq);
     }
     else 
     {
         for (int i = 0; i < islandSizeSq; i++)
             if (mWolfStorrageArray[i].isAlive)
                 mWolfStorrageArray[i].hunt(rabbitIsland, mWolfIsland, rabbitStorageArray, &rabbitsAlive, islandSizeSq);
         for (int i = 0; i < islandSizeSq; i++)
             if (fWolfStorrageArray[i].isAlive)
                 fWolfStorrageArray[i].hunt(rabbitIsland, fWolfIsland, rabbitStorageArray, &rabbitsAlive, islandSizeSq);

     }
     whoHuntsFirst = !whoHuntsFirst;
     sortStorageArray(rabbitStorageArray, &rabbitStartID, islandSize);
     //wolfs move
     for (int i = 0; i < islandSizeSq; i++)
         if (fWolfStorrageArray[i].isAlive)
             fWolfStorrageArray[i].move(fWolfIsland);
     for (int i = 0; i < islandSizeSq; i++)
         if (mWolfStorrageArray[i].isAlive)
             mWolfStorrageArray[i].move(mWolfIsland);
     //reseting the reproduce timer
     for (int i = 0; i < islandSizeSq; i++)
         if (mWolfStorrageArray[i].isAlive)
             mWolfStorrageArray[i].reproduceTimerReduce();
     //burning calories
     for (int i = 0; i < islandSizeSq; i++)
     {
         if (mWolfStorrageArray[i].isAlive)
             mWolfStorrageArray[i].burnCalories(mWolfIsland, &mWolfsAlive);
         if (fWolfStorrageArray[i].isAlive)
             fWolfStorrageArray[i].burnCalories(fWolfIsland, &fWolfsAlive);
     }
     //generating custom hedge
     if (isHedgeEnabled && wasCustomHedgeModified)
         {
             for (int i = 0; i < islandSizeSq; i++)
                 if (fWolfStorrageArray[i].isAlive)
                     if (customHedge.getField(fWolfStorrageArray[i].pos.x-5, fWolfStorrageArray[i].pos.y-5) == 3)
                         fWolfStorrageArray[i].kill(fWolfIsland, &fWolfsAlive);
             for (int i = 0; i < islandSizeSq; i++)
                 if (mWolfStorrageArray[i].isAlive)
                     if (customHedge.getField(mWolfStorrageArray[i].pos.x-5, mWolfStorrageArray[i].pos.y-5) == 3)
                         mWolfStorrageArray[i].kill(mWolfIsland, &mWolfsAlive);
             for (int i = 0; i < islandSize; i++)
                 for (int j = 0; j < islandSize; j++)
                     if (customHedge.getField(i, j) == 3)
                     {
                         fWolfIsland.setField(3, i+5, j+5);
                         mWolfIsland.setField(3, i+5, j+5);
                     }
             wasCustomHedgeModified = false;
             isHedgeGenerated = true;
         }
     //destroying the hedge
     if (!isHedgeEnabled && isHedgeGenerated)
     {
         mWolfIsland.clearHedge();
         fWolfIsland.clearHedge();
         isHedgeGenerated = false;
     }

}
void Simulation::draw(sf::RenderWindow& mainWindow, sf::RectangleShape& ocean, sf::RectangleShape& islandView, sf::RectangleShape& rabbitView, sf::CircleShape& fWolfView, sf::CircleShape& mWolfView, sf::Font& font1, bool isHedgeEnabled)
{
    int i;
    islandView.setPosition(30, 30);
    mainWindow.draw(ocean);
    mainWindow.draw(islandView);

    if(isHedgeEnabled)
    {
        rabbitView.setFillColor(sf::Color(0, 168, 107, 255));
        for (int i = 0; i < islandSize + 5; i++)
            for (int j = 0; j < islandSize + 5; j++)
                if (fWolfIsland.getField(i, j) == 3)
                {
                    rabbitView.setPosition(i * 10 - 20, j * 10 - 20);
                    mainWindow.draw(rabbitView);
                }
        rabbitView.setFillColor(sf::Color::White);
    }

    for (i = 0; i < islandSizeSq; i++)
        if (rabbitStorageArray[i].isAlive)
        {
            rabbitView.setPosition((rabbitStorageArray[i].pos.x * 10) - 20, (rabbitStorageArray[i].pos.y * 10) - 20);
            mainWindow.draw(rabbitView);
        }
    for (i = 0; i < islandSizeSq; i++)
        if (fWolfStorrageArray[i].isAlive)
        {
            fWolfView.setPosition((fWolfStorrageArray[i].pos.x * 10) - 20, (fWolfStorrageArray[i].pos.y * 10) - 20);
            mainWindow.draw(fWolfView);
        }
    for (i = 0; i < islandSizeSq; i++)
        if (mWolfStorrageArray[i].isAlive)
        {
            mWolfView.setPosition((mWolfStorrageArray[i].pos.x * 10) - 20, (mWolfStorrageArray[i].pos.y * 10) - 20);
            mainWindow.draw(mWolfView);
        }

    std::string str1 = "Rabbits alive: ";
    str1 = str1 + std::to_string(rabbitsAlive);
    std::string str2 = "Female wolfs alive: ";
    str2 = str2 + std::to_string(fWolfsAlive);
    std::string str3 = "Male wolfs alive: ";
    str3 = str3 + std::to_string(mWolfsAlive);
    std::string str4 = "Rabbits dead: ";
    str4 = str4 + std::to_string(allRabits - rabbitsAlive);
    std::string str5 = "F. wolfs dead: ";
    str5 = str5 + std::to_string(allFWolfs - fWolfsAlive);
    std::string str6 = "M. wolfs dead: ";
    str6 = str6 + std::to_string(allMWolfs - mWolfsAlive);

    sf::Text text1;
    sf::Text text2;
    sf::Text text3;
    sf::Text text4;
    sf::Text text5;
    sf::Text text6;
    text1.setFont(font1);
    text2.setFont(font1);
    text3.setFont(font1);
    text4.setFont(font1);
    text5.setFont(font1);
    text6.setFont(font1);
    text1.setString(str1);
    text2.setString(str2);
    text3.setString(str3);
    text4.setString(str4);
    text5.setString(str5);
    text6.setString(str6);
    text1.setCharacterSize(18);
    text2.setCharacterSize(18);
    text3.setCharacterSize(18);
    text4.setCharacterSize(18);
    text5.setCharacterSize(18);
    text6.setCharacterSize(18);
    text1.setFillColor(sf::Color(255, 255, 255, 255));
    text2.setFillColor(sf::Color(255, 255, 255, 255));
    text3.setFillColor(sf::Color(255, 255, 255, 255));
    text4.setFillColor(sf::Color::White);
    text5.setFillColor(sf::Color::White);
    text6.setFillColor(sf::Color::White);
    text1.setPosition(islandSize * 10 + 65, 5);
    text2.setPosition(islandSize * 10 + 65, 25);
    text3.setPosition(islandSize * 10 + 65, 45);
    text4.setPosition(islandSize * 10 + 65, 65);
    text5.setPosition(islandSize * 10 + 65, 85);
    text6.setPosition(islandSize * 10 + 65, 105);
    mainWindow.draw(text1);
    mainWindow.draw(text2);
    mainWindow.draw(text3);
    mainWindow.draw(text4);
    mainWindow.draw(text5);
    mainWindow.draw(text6);
}

Simulation::~Simulation()
{
    if (isSimInitiated)
    {
        delete[] rabbitStorageArray;
        delete[] fWolfStorrageArray;
        delete[] mWolfStorrageArray;
    }
    isHedgeGenerated = false;
}

void Simulation::addRabbit(int posX, int posY)
{
    if (posX > 2 && posX < islandSize+5 && posY > 2 && posY < islandSize+5)
    {
        if (rabbitIsland.getField(posX, posY) == 0)
        {
            rabbitStorageArray[rabbitStartID].create(rabbitIsland, rabbitStartID, posX, posY);
            rabbitsAlive++;
            allRabits++;
            rabbitStartID++;
        }
    }
}

void Simulation::addFWolf(int posX, int posY)
{
    if (posX > 2 && posX < islandSize + 5 && posY > 2 && posY < islandSize + 5)
    {
        if (fWolfIsland.getField(posX, posY) == 0)
        {
            fWolfStorrageArray[fWolfStartID].create(fWolfIsland, fWolfStartID, posX, posY);
            fWolfsAlive++;
            allFWolfs++;
            fWolfStartID++;
        }
    }
}

void Simulation::addMWolf(int posX, int posY)
{
    if (posX > 2 && posX < islandSize + 5 && posY > 2 && posY < islandSize + 5)
    {
        if (mWolfIsland.getField(posX, posY) == 0)
        {
            mWolfStorrageArray[mWolfStartID].create(mWolfIsland, mWolfStartID, posX, posY);
            mWolfsAlive++;
            allMWolfs++;
            mWolfStartID++;
        }
    }
}

void sortStorageArray(Rabbit StorageArray[], int* StartID, int islandSize) {
    int i;
    int islandSizeSq = islandSize * islandSize;
    Rabbit* tempStorageArray = new Rabbit[islandSizeSq];
    int tempID = 0; //from this id forward all entities in the tempEntityArray are dead (including the entity under this index)
    for (i = 0; i < islandSizeSq; i++) {
        if (StorageArray[i].isAlive) {
            tempStorageArray[tempID] = StorageArray[i];
            tempID++;
        }
    }
    for (i = 0; i < islandSizeSq; i++)
        StorageArray[i] = tempStorageArray[i];
    (*StartID) = tempID;
    delete[] tempStorageArray;
}

void sortStorageArray(FWolf StorageArray[], int* StartID, int islandSize) {
    int i;
    int islandSizeSq = islandSize * islandSize;
    FWolf* tempStorageArray = new FWolf [islandSizeSq];
    int tempID = 0; //from this id forward all entities in the tempEntityArray are dead (including the entity under this index)
    for (i = 0; i < islandSizeSq; i++) {
        if (StorageArray[i].isAlive) {
            tempStorageArray[tempID] = StorageArray[i];
            tempID++;
        }
    }
    for (i = 0; i < islandSizeSq; i++)
        StorageArray[i] = tempStorageArray[i];
    (*StartID) = tempID;
    delete[] tempStorageArray;
}

void sortStorageArray(MWolf StorageArray[], int* StartID, int islandSize) {
    int i;
    int islandSizeSq = islandSize * islandSize;
    MWolf* tempStorageArray =new MWolf[islandSizeSq];
    int tempID = 0; //from this id forward all entities in the tempEntityArray are dead (including the entity under this index)
    for (i = 0; i < islandSizeSq; i++) {
        if (StorageArray[i].isAlive) {
            tempStorageArray[tempID] = StorageArray[i];
            tempID++;
        }
    }
    for (i = 0; i < islandSizeSq; i++)
        StorageArray[i] = tempStorageArray[i];
    (*StartID) = tempID;
    delete[] tempStorageArray;
}