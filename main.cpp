#include <chrono>
#include <sstream>
#include "Simulation.h"
#include "Button.h"
#include "CustomHedgeMatrix.h"

int main()
{
    //varaibles used for storing the island size
    int islandSize = 40;
    int islandSizeSq = islandSize * islandSize;

    //RNG seeding
    srand(time(0));

    //Font loading
    sf::Font font1;
    font1.loadFromFile("SFPixelate-Bold.ttf");

    //Creating the main window with the island view and controls
    sf::RenderWindow mainWindow(sf::VideoMode(750, 460), "Wolf Island", sf::Style::Titlebar | sf::Style::Close);
    sf::RenderWindow helpWindow;

    //Creating shapes
    sf::RectangleShape ocean(sf::Vector2f(islandSize * 10 + 60, islandSize * 10 + 60));
    sf::RectangleShape islandView(sf::Vector2f(islandSize * 10, islandSize * 10));
    sf::RectangleShape rabbitView(sf::Vector2f(10, 10));
    sf::CircleShape fWolfView(5.f);
    sf::CircleShape mWolfView(5.f, 4);
    sf::RectangleShape pauseBackground(sf::Vector2f(80, 25));

    //Selecting colors for the shapes
    ocean.setFillColor(sf::Color(137,207,240,255));
    islandView.setFillColor(sf::Color(116,195,101,255));
    rabbitView.setFillColor(sf::Color(255, 255, 255, 255));
    fWolfView.setFillColor(sf::Color(159, 129, 112, 255));
    mWolfView.setFillColor(sf::Color(145,163,176,255));
    pauseBackground.setFillColor(sf::Color::Black);
    //creating a Simulation object
    Simulation sim1;

    //creating cutom hedge matrix
    CustomHedgeMatrix customHedge1;

    //time variables used for controling simulation speed and frame rate
    std::chrono::steady_clock::time_point time1;
    std::chrono::steady_clock::time_point time2;
    std::chrono::steady_clock::time_point frameTime1;
    std::chrono::steady_clock::time_point frameTime2;
    std::chrono::duration<float> elapsed;
    std::chrono::duration<float> elapsedFrameTime;


    //other variables
    int iter = 0; //current iteration number
    int speed = 1; //maximum speed in iterations per second
    bool startSim = false; //determines whether the simulation shuold start or not
    bool isSimRunning = false; //false - simulation is not running, true - simulation is running
    bool isSpeedUnlimited = false; //false - the maximum simulation speed will be equal to int speed, true - the maximum simulation speed will be unlimited, it will run as fast as possible
    bool isPaused = false; //determines whether the simulation is paused
    bool areAdvancedOptionsVisible = false;
    bool isCustomHedgeApproved = false;
    bool wasCustomHedgeModified = false;
    bool isHedgeEnabled = false; //true - hedge is enabled, false - hedge is disabled
    bool genereateHedgeOnNextClick = false; //determines whether the hedge should be generated on the next LMB click
    bool isHedgeStateChangeAllowed = true; //determines whether the hedge can be change; note that it's only possible to generate a hedge once per simulation cycle
    int startRabbitsAmount = 25; //amount of rabbits at the beggining of the simulation
    int startfWolfsAmount = 10; //amount of female wolfs at the begging of the simulation
    int startmWolfsAmount = 10; //amount of male wolfs at the begging of the simulation
    int blinkPauseCounter = 0; //used for making the paused text blink
    int blinkSimOverCounter = 60; //used for making the simulation over text blink

    int drawMode = 4; //1 - rabbits, 2 - female wolfs, 3 - male wolfs, 4 - hedge

    //Buttons used in the main menu
    Button StartButton({ 200,60 }, { 275,240 }, { 312,242 }, "Start", 42, font1);
    Button ExitButton({ 200,60 }, { 275,380 }, { 328,382 }, "Exit", 42, font1);
    Button AdvancedButton({ 200,60 }, { 275,310 }, { 330,312 }, "Adv.", 42, font1);
    Button minus1({ 30,30 }, { 430,23 }, { 440,27 }, "-", 18, font1);
    Button minus2({ 30,30 }, { 430,72 }, { 440,76 }, "-", 18, font1);
    Button minus3({ 30,30 }, { 430,121 }, { 440,125 }, "-", 18, font1);
    Button minus4({ 30,30 }, { 430,170 }, { 440,174 }, "-", 18, font1);
    Button plus1({ 30,30 }, { 530,23 }, { 540,27 }, "+", 18, font1);
    Button plus2({ 30,30 }, { 530,72 }, { 540,76 }, "+", 18, font1);
    Button plus3({ 30,30 }, { 530,121 }, { 540,125 }, "+", 18, font1);
    Button plus4({ 30,30 }, { 530,170 }, { 540,174 }, "+", 18, font1);

    //text object for the main menu
    sf::Text rabbits;
    sf::Text fWolfs;
    sf::Text mWolfs;
    sf::Text rabbitsAmount;
    sf::Text fWolfsAmount;
    sf::Text mWolfsAmount;
    sf::Text IslandSizeText;
    sf::Text IslandSizeValue;
    sf::Text PressHToOpenHelpWindow;
    rabbits.setFont(font1);
    rabbits.setString("Rabbits");
    rabbits.setCharacterSize(28);
    rabbits.setFillColor(sf::Color::White);
    rabbits.setPosition(185, 20);
    fWolfs.setFont(font1);
    fWolfs.setString("Female Wolfs");
    fWolfs.setCharacterSize(28);
    fWolfs.setFillColor(sf::Color::White);
    fWolfs.setPosition(185, 70);
    mWolfs.setFont(font1);
    mWolfs.setString("Male Wolfs");
    mWolfs.setCharacterSize(28);
    mWolfs.setFillColor(sf::Color::White);
    mWolfs.setPosition(185, 120);
    rabbitsAmount.setFont(font1);
    rabbitsAmount.setString(std::to_string(startRabbitsAmount));
    rabbitsAmount.setCharacterSize(28);
    rabbitsAmount.setFillColor(sf::Color::White);
    rabbitsAmount.setPosition(478, 21);
    fWolfsAmount.setFont(font1);
    fWolfsAmount.setString(std::to_string(startfWolfsAmount));
    fWolfsAmount.setCharacterSize(28);
    fWolfsAmount.setFillColor(sf::Color::White);
    fWolfsAmount.setPosition(478, 70);
    mWolfsAmount.setFont(font1);
    mWolfsAmount.setString(std::to_string(startmWolfsAmount));
    mWolfsAmount.setCharacterSize(28);
    mWolfsAmount.setFillColor(sf::Color::White);
    mWolfsAmount.setPosition(478, 119);
    IslandSizeText.setFont(font1);
    IslandSizeText.setString("Island Size");
    IslandSizeText.setCharacterSize(28);
    IslandSizeText.setFillColor(sf::Color::White);
    IslandSizeText.setPosition(185, 170);
    IslandSizeValue.setFont(font1);
    IslandSizeValue.setString(std::to_string(islandSize));
    IslandSizeValue.setCharacterSize(28);
    IslandSizeValue.setFillColor(sf::Color::White);
    IslandSizeValue.setPosition(478, 168);
    PressHToOpenHelpWindow.setFont(font1);
    PressHToOpenHelpWindow.setString("Press H to open Help Window");
    PressHToOpenHelpWindow.setCharacterSize(14);
    PressHToOpenHelpWindow.setFillColor(sf::Color::White);
    PressHToOpenHelpWindow.setPosition(500, 435);

    //buttons for the advanced options menu
    Button Back({ 200,60 }, { 275,380 }, { 318,382 }, "Back", 42, font1);
    Button minus5({ 30,30 }, { 500,23 }, { 510,27 }, "-", 18, font1);
    Button minus6({ 30,30 }, { 500,72 }, { 510,76 }, "-", 18, font1);
    Button minus7({ 30,30 }, { 500,121 }, { 510,125 }, "-", 18, font1);
    Button minus8({ 30,30 }, { 500,170 }, { 510,174 }, "-", 18, font1);
    Button minus9({ 30,30 }, { 500,219 }, { 510,223 }, "-", 18, font1);
    Button plus5({ 30,30 }, { 640,23 }, { 650,27 }, "+", 18, font1);
    Button plus6({ 30,30 }, { 640,72 }, { 650,76 }, "+", 18, font1);
    Button plus7({ 30,30 }, { 640,121 }, { 650,125 }, "+", 18, font1);
    Button plus8({ 30,30 }, { 640,170 }, { 650,174 }, "+", 18, font1);
    Button plus9({ 30,30 }, { 640,219 }, { 650,223 }, "+", 18, font1);


    //text object for the advanced options menu
    sf::Text rabbitReproducitonFactor;
    sf::Text wolfReproductionTimer;
    sf::Text wolfMaxFat;
    sf::Text wolfStartFat;
    sf::Text wolfFatPerRabbit;

    std::ostringstream tempostringstream; //temp variable for setting float precision for displaying
    tempostringstream.precision(1);
    sf::Text rabbitReproducitonFactorValueText;
    sf::Text wolfReproductionTimerValueText;
    sf::Text wolfMaxFatValueText;
    sf::Text wolfStartFatValueText;
    sf::Text wolfFatPerRabbitValueText;

    rabbitReproducitonFactor.setFont(font1);
    rabbitReproducitonFactor.setCharacterSize(28);
    rabbitReproducitonFactor.setFillColor(sf::Color::White);
    rabbitReproducitonFactor.setString("Rabbit reproduction factor");
    rabbitReproducitonFactor.setPosition(20, 20);
    wolfReproductionTimer.setFont(font1);
    wolfReproductionTimer.setCharacterSize(28);
    wolfReproductionTimer.setFillColor(sf::Color::White);
    wolfReproductionTimer.setString("Wolf reproduction timer");
    wolfReproductionTimer.setPosition(20, 70);
    wolfMaxFat.setFont(font1);
    wolfMaxFat.setCharacterSize(28);
    wolfMaxFat.setFillColor(sf::Color::White);
    wolfMaxFat.setString("Wolf's maximum stored fat");
    wolfMaxFat.setPosition(20, 120);
    wolfStartFat.setFont(font1);
    wolfStartFat.setCharacterSize(28);
    wolfStartFat.setFillColor(sf::Color::White);
    wolfStartFat.setString("Newborn wolf's stored fat");
    wolfStartFat.setPosition(20, 170);
    wolfFatPerRabbit.setFont(font1);
    wolfFatPerRabbit.setCharacterSize(28);
    wolfFatPerRabbit.setFillColor(sf::Color::White);
    wolfFatPerRabbit.setString("Fat per rabbit consumed");
    wolfFatPerRabbit.setPosition(20, 220);

    rabbitReproducitonFactorValueText.setFont(font1);
    rabbitReproducitonFactorValueText.setCharacterSize(28);
    rabbitReproducitonFactorValueText.setFillColor(sf::Color::White);
    rabbitReproducitonFactorValueText.setString(std::to_string(rabbitReproducitonFactorValue));
    rabbitReproducitonFactorValueText.setPosition(548,20);
    wolfReproductionTimerValueText.setFont(font1);
    wolfReproductionTimerValueText.setCharacterSize(28);
    wolfReproductionTimerValueText.setFillColor(sf::Color::White);
    wolfReproductionTimerValueText.setString(std::to_string(wolfReproductionTimerValue));
    wolfReproductionTimerValueText.setPosition(548, 70);
    wolfMaxFatValueText.setFont(font1);
    wolfMaxFatValueText.setCharacterSize(28);
    wolfMaxFatValueText.setFillColor(sf::Color::White);
    tempostringstream << std::fixed << wolfMaxFatValue;
    wolfStartFatValueText.setString(tempostringstream.str());
    tempostringstream.str(""); //clearing tempostringstream buffer
    wolfMaxFatValueText.setPosition(548, 120);
    wolfStartFatValueText.setFont(font1);
    wolfStartFatValueText.setCharacterSize(28);
    wolfStartFatValueText.setFillColor(sf::Color::White);
    tempostringstream << std::fixed << wolfStartFatValue;
    wolfStartFatValueText.setString(tempostringstream.str());
    tempostringstream.str(""); //clearing tempostringstream buffer
    wolfStartFatValueText.setPosition(548, 170);
    wolfFatPerRabbitValueText.setFont(font1);
    wolfFatPerRabbitValueText.setCharacterSize(28);
    wolfFatPerRabbitValueText.setFillColor(sf::Color::White);
    tempostringstream << std::fixed << wolfFatPerRabbitValue;
    wolfFatPerRabbitValueText.setString(tempostringstream.str());
    wolfFatPerRabbitValueText.setPosition(548, 220);
    tempostringstream.str(""); //clearing tempostringstream buffer



    //helpWindow content
    sf::Text htext1;
    sf::Text htext2;
    sf::Text htext3;
    sf::Text htext4;
    sf::Text htext5;
    sf::Text htext6;
    sf::Text htext7;
    sf::Text htext8;
    sf::Text htext9;
    sf::Text htext10;
    sf::Text htext11;
    sf::Text htext12;
    sf::Text htext13;
    sf::Text htext14;
    sf::Text htext15;
    sf::Text htext16;
    sf::Text htext17;
    htext1.setFont(font1);
    htext2.setFont(font1);
    htext3.setFont(font1);
    htext4.setFont(font1);
    htext5.setFont(font1);
    htext6.setFont(font1);
    htext7.setFont(font1);
    htext8.setFont(font1);
    htext9.setFont(font1);
    htext10.setFont(font1);
    htext11.setFont(font1);
    htext12.setFont(font1);
    htext13.setFont(font1);
    htext14.setFont(font1);
    htext15.setFont(font1);
    htext16.setFont(font1);
    htext17.setFont(font1);
    htext1.setCharacterSize(20);
    htext2.setCharacterSize(14);
    htext3.setCharacterSize(14);
    htext4.setCharacterSize(14);
    htext5.setCharacterSize(14);
    htext6.setCharacterSize(14);
    htext7.setCharacterSize(14);
    htext8.setCharacterSize(14);
    htext9.setCharacterSize(14);
    htext10.setCharacterSize(20);
    htext11.setCharacterSize(14);
    htext12.setCharacterSize(20);
    htext13.setCharacterSize(14);
    htext14.setCharacterSize(14);
    htext15.setCharacterSize(14);
    htext16.setCharacterSize(20);
    htext17.setCharacterSize(14);
    htext1.setFillColor(sf::Color::White);
    htext2.setFillColor(sf::Color::White);
    htext3.setFillColor(sf::Color::White);
    htext4.setFillColor(sf::Color::White);
    htext5.setFillColor(sf::Color::White);
    htext6.setFillColor(sf::Color::White);
    htext7.setFillColor(sf::Color::White);
    htext8.setFillColor(sf::Color::White);
    htext9.setFillColor(sf::Color::White);
    htext10.setFillColor(sf::Color::White);
    htext11.setFillColor(sf::Color::White);
    htext12.setFillColor(sf::Color::White);
    htext13.setFillColor(sf::Color::White);
    htext14.setFillColor(sf::Color::White);
    htext15.setFillColor(sf::Color::White);
    htext16.setFillColor(sf::Color::White);
    htext17.setFillColor(sf::Color::White);
    htext1.setPosition(10, 10);
    htext2.setPosition(10, 40);
    htext3.setPosition(10, 60);
    htext4.setPosition(10, 80);
    htext5.setPosition(10, 100);
    htext6.setPosition(10, 120);
    htext7.setPosition(10, 140);
    htext8.setPosition(10, 160);
    htext9.setPosition(10, 180);
    htext10.setPosition(10, 220);
    htext11.setPosition(10, 250);
    htext12.setPosition(10, 445);
    htext13.setPosition(30, 481);
    htext14.setPosition(30, 501);
    htext15.setPosition(30, 521);
    htext16.setPosition(10, 555);
    htext17.setPosition(10, 590);
    htext1.setString("Controls");
    htext2.setString("S - Decrease simulation speed");
    htext3.setString("F - Increase simulation speed");
    htext4.setString("M - Set speed to maximum");
    htext5.setString("D - Set speed to minimum");
    htext6.setString("Space - Pause/Resume");
    htext7.setString("Esc - Return to main menu");
    htext8.setString("LMB - Draw hedge");
    htext9.setString("RMB - Clear hedge/hedge markers");
    htext10.setString("Drawing The Hedge");
    htext11.setString("Move your cursor over the postion\nwhere you want to have the first\ncorner of your hedge  and  press\nthe   LMB    (Left Mouse Button).\n"
        "A  yellow   marker  will   appear.\nAfterwards   move   your  cursor\nover another position  where  you\nwish to have the  second  corner\nof the hedge and press  the  LMB\nagain."
        " A second yellow marker will\nappera with a blue outline of  the\nhedge. Press  the  LMB  again  to\nbuild  the  hedge.  Note  that  the\nminimal hedge size is 3x3.");
    htext12.setString("Key");
    htext13.setString("Rabbit");
    htext14.setString("Female Wolf");
    htext15.setString("Male Wolf");
    htext16.setString("Main menu");
    htext17.setString("Press the  +/-  button  with  your\ncursor   to   change   the   given\nparameter. Note that you can hold\nLeft  Ctrl  while  pressing  LMB"
        " in\norder   to   increase/decrease  a\nparameter by 10 instead of 1.");

    //mainWindow loop
    while (mainWindow.isOpen())
    {
        sf::Event event1;
        sf::Event event2;

        //main menu
        while (!startSim)
        {
            //helpWindow loop
            while (helpWindow.isOpen() && helpWindow.hasFocus())
            {
                while (helpWindow.pollEvent(event2))
                {
                    if (event2.type == event2.Closed)
                    {
                        helpWindow.close();
                    }
                }
                Sleep(50);
            }

            mainWindow.clear();
            rabbitsAmount.setString(std::to_string(startRabbitsAmount));
            fWolfsAmount.setString(std::to_string(startfWolfsAmount));
            mWolfsAmount.setString(std::to_string(startmWolfsAmount));
            IslandSizeValue.setString(std::to_string(islandSize));

            while (mainWindow.pollEvent(event1))
            {
                if (event1.type == event1.Closed)
                {
                    mainWindow.close();
                    return 0;
                }
                if (event1.type == event1.KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H))
                {
                    //opening the helpWindow
                    helpWindow.create(sf::VideoMode(310, 685), "Wolf Island - help", sf::Style::Titlebar | sf::Style::Close);
                    helpWindow.draw(htext1);
                    helpWindow.draw(htext2);
                    helpWindow.draw(htext3);
                    helpWindow.draw(htext4);
                    helpWindow.draw(htext5);
                    helpWindow.draw(htext6);
                    helpWindow.draw(htext7);
                    helpWindow.draw(htext8);
                    helpWindow.draw(htext9);
                    helpWindow.draw(htext10);
                    helpWindow.draw(htext11);
                    helpWindow.draw(htext12);
                    helpWindow.draw(htext13);
                    helpWindow.draw(htext14);
                    helpWindow.draw(htext15);
                    helpWindow.draw(htext16);
                    helpWindow.draw(htext17);

                    rabbitView.setPosition(10, 485);
                    fWolfView.setPosition(10, 505);
                    mWolfView.setPosition(10, 525);
                    helpWindow.draw(rabbitView);
                    helpWindow.draw(fWolfView);
                    helpWindow.draw(mWolfView);
                    helpWindow.display();
                }
                if (!areAdvancedOptionsVisible) //main menu
                {
                    //checking whether a button was pressed in the main menu and taking appropriate actions
                    if (event1.type == event1.MouseButtonPressed && StartButton.isCursorOver(mainWindow))
                        startSim = true;
                    if (event1.type == event1.MouseButtonPressed && ExitButton.isCursorOver(mainWindow))
                    {
                        mainWindow.close();
                        return 0;
                    }
                    if (event1.type == event1.MouseButtonPressed && AdvancedButton.isCursorOver(mainWindow))
                    {
                        areAdvancedOptionsVisible = true;
                        mainWindow.clear();
                    }
                    if (event1.type == event1.MouseButtonPressed && minus1.isCursorOver(mainWindow) && startRabbitsAmount > 1)
                        startRabbitsAmount--;
                    if (event1.type == event1.MouseButtonPressed && plus1.isCursorOver(mainWindow) && startRabbitsAmount < 99)
                        startRabbitsAmount++;
                    if (event1.type == event1.MouseButtonPressed && minus2.isCursorOver(mainWindow) && startfWolfsAmount > 1)
                        startfWolfsAmount--;
                    if (event1.type == event1.MouseButtonPressed && plus2.isCursorOver(mainWindow) && startfWolfsAmount < 99)
                        startfWolfsAmount++;
                    if (event1.type == event1.MouseButtonPressed && minus3.isCursorOver(mainWindow) && startmWolfsAmount > 1)
                        startmWolfsAmount--;
                    if (event1.type == event1.MouseButtonPressed && plus3.isCursorOver(mainWindow) && startmWolfsAmount < 99)
                        startmWolfsAmount++;
                    if (event1.type == event1.MouseButtonPressed && minus4.isCursorOver(mainWindow) && islandSize > 10)
                        islandSize--;
                    if (event1.type == event1.MouseButtonPressed && plus4.isCursorOver(mainWindow) && islandSize < 80)
                        islandSize++;

                    if (event1.type == event1.MouseButtonPressed && minus1.isCursorOver(mainWindow) && startRabbitsAmount > 10 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        startRabbitsAmount -= 9;
                    if (event1.type == event1.MouseButtonPressed && plus1.isCursorOver(mainWindow) && startRabbitsAmount < 90 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        startRabbitsAmount += 9;
                    if (event1.type == event1.MouseButtonPressed && minus2.isCursorOver(mainWindow) && startfWolfsAmount > 10 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        startfWolfsAmount -= 9;
                    if (event1.type == event1.MouseButtonPressed && plus2.isCursorOver(mainWindow) && startfWolfsAmount < 90 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        startfWolfsAmount += 9;
                    if (event1.type == event1.MouseButtonPressed && minus3.isCursorOver(mainWindow) && startmWolfsAmount > 10 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        startmWolfsAmount -= 9;
                    if (event1.type == event1.MouseButtonPressed && plus3.isCursorOver(mainWindow) && startmWolfsAmount < 90 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        startmWolfsAmount += 9;
                    if (event1.type == event1.MouseButtonPressed && minus4.isCursorOver(mainWindow) && islandSize > 20 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        islandSize -= 9;
                    if (event1.type == event1.MouseButtonPressed && plus4.isCursorOver(mainWindow) && islandSize < 70 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        islandSize += 9;
                }
                else //advanced options menu
                {
                    if (event1.type == event1.MouseButtonPressed && Back.isCursorOver(mainWindow))
                        areAdvancedOptionsVisible = false;

                    if (event1.type == event1.MouseButtonPressed && minus5.isCursorOver(mainWindow) && rabbitReproducitonFactorValue > 1)
                        rabbitReproducitonFactorValue--;
                    if (event1.type == event1.MouseButtonPressed && plus5.isCursorOver(mainWindow) && rabbitReproducitonFactorValue < 50)
                        rabbitReproducitonFactorValue++;
                    if (event1.type == event1.MouseButtonPressed && minus6.isCursorOver(mainWindow) && wolfReproductionTimerValue > 1)
                        wolfReproductionTimerValue--;
                    if (event1.type == event1.MouseButtonPressed && plus6.isCursorOver(mainWindow) && wolfReproductionTimerValue < 500)
                        wolfReproductionTimerValue++;
                    if (event1.type == event1.MouseButtonPressed && minus7.isCursorOver(mainWindow) && wolfMaxFatValue > 1)
                        wolfMaxFatValue--;
                    if (event1.type == event1.MouseButtonPressed && plus7.isCursorOver(mainWindow) && wolfMaxFatValue < 500)
                        wolfMaxFatValue++;
                    if (event1.type == event1.MouseButtonPressed && minus8.isCursorOver(mainWindow) && wolfStartFatValue > 1)
                        wolfStartFatValue-=0.1;
                    if (event1.type == event1.MouseButtonPressed && plus8.isCursorOver(mainWindow) && wolfStartFatValue < 30)
                        wolfStartFatValue+=0.1;
                    if (event1.type == event1.MouseButtonPressed && minus9.isCursorOver(mainWindow) && wolfFatPerRabbitValue > 1)
                        wolfFatPerRabbitValue-=0.1;
                    if (event1.type == event1.MouseButtonPressed && plus9.isCursorOver(mainWindow) && wolfFatPerRabbitValue < 50)
                        wolfFatPerRabbitValue+=0.1;

                    if (event1.type == event1.MouseButtonPressed && minus5.isCursorOver(mainWindow) && rabbitReproducitonFactorValue > 10 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        rabbitReproducitonFactorValue-=9;
                    if (event1.type == event1.MouseButtonPressed && plus5.isCursorOver(mainWindow) && rabbitReproducitonFactorValue < 40 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        rabbitReproducitonFactorValue+=9;
                    if (event1.type == event1.MouseButtonPressed && minus6.isCursorOver(mainWindow) && wolfReproductionTimerValue > 10 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        wolfReproductionTimerValue-=9;
                    if (event1.type == event1.MouseButtonPressed && plus6.isCursorOver(mainWindow) && wolfReproductionTimerValue < 490 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        wolfReproductionTimerValue+=9;
                    if (event1.type == event1.MouseButtonPressed && minus7.isCursorOver(mainWindow) && wolfMaxFatValue > 10 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        wolfMaxFatValue-=9;
                    if (event1.type == event1.MouseButtonPressed && plus7.isCursorOver(mainWindow) && wolfMaxFatValue < 490 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        wolfMaxFatValue+=9;
                    if (event1.type == event1.MouseButtonPressed && minus8.isCursorOver(mainWindow) && wolfStartFatValue > 2 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        wolfStartFatValue -= 0.9;
                    if (event1.type == event1.MouseButtonPressed && plus8.isCursorOver(mainWindow) && wolfStartFatValue < 29 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        wolfStartFatValue += 0.9;
                    if (event1.type == event1.MouseButtonPressed && minus9.isCursorOver(mainWindow) && wolfFatPerRabbitValue > 2 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        wolfFatPerRabbitValue -= 0.9;
                    if (event1.type == event1.MouseButtonPressed && plus9.isCursorOver(mainWindow) && wolfFatPerRabbitValue < 49 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        wolfFatPerRabbitValue += 0.9;
                }
            }
            //corecting variables
            if (wolfStartFatValue < 1)
                wolfStartFatValue = 1;
            if (wolfStartFatValue > 30)
                wolfStartFatValue = 30;
            if (wolfFatPerRabbitValue < 1)
                wolfFatPerRabbitValue = 1;
            if (wolfFatPerRabbitValue > 50)
                wolfFatPerRabbitValue = 50;

            //updating variables in the advanced options menu
            rabbitReproducitonFactorValueText.setString(std::to_string(rabbitReproducitonFactorValue));
            wolfReproductionTimerValueText.setString(std::to_string(wolfReproductionTimerValue));
            tempostringstream.precision(0);
            tempostringstream.str(""); //clearing tempostringstream buffer
            tempostringstream << std::fixed << wolfMaxFatValue;
            wolfMaxFatValueText.setString(tempostringstream.str());
            tempostringstream.precision(1);
            tempostringstream.str(""); //clearing tempostringstream buffer
            tempostringstream << std::fixed << wolfStartFatValue;
            wolfStartFatValueText.setString(tempostringstream.str());
            tempostringstream.str(""); //clearing tempostringstream buffer
            tempostringstream << std::fixed << wolfFatPerRabbitValue;
            wolfFatPerRabbitValueText.setString(tempostringstream.str());
            tempostringstream.str(""); //clearing tempostringstream buffer

            //updating the islandSizeSq variable
            islandSizeSq = islandSize * islandSize;

            //rendering the main menu
            if (!areAdvancedOptionsVisible)
            {
                StartButton.draw(mainWindow);
                ExitButton.draw(mainWindow);
                AdvancedButton.draw(mainWindow);
                minus1.draw(mainWindow);
                minus2.draw(mainWindow);
                minus3.draw(mainWindow);
                minus4.draw(mainWindow);
                plus1.draw(mainWindow);
                plus2.draw(mainWindow);
                plus3.draw(mainWindow);
                plus4.draw(mainWindow);

                mainWindow.draw(rabbits);
                mainWindow.draw(fWolfs);
                mainWindow.draw(mWolfs);
                mainWindow.draw(rabbitsAmount);
                mainWindow.draw(fWolfsAmount);
                mainWindow.draw(mWolfsAmount);
                mainWindow.draw(IslandSizeText);
                mainWindow.draw(IslandSizeValue);
                mainWindow.draw(PressHToOpenHelpWindow);
            }
            else
            {
                mainWindow.draw(rabbitReproducitonFactor);
                mainWindow.draw(wolfReproductionTimer);
                mainWindow.draw(wolfMaxFat);
                mainWindow.draw(wolfStartFat);
                mainWindow.draw(wolfFatPerRabbit);
                mainWindow.draw(rabbitReproducitonFactorValueText);
                mainWindow.draw(wolfReproductionTimerValueText);
                mainWindow.draw(wolfMaxFatValueText);
                mainWindow.draw(wolfStartFatValueText);
                mainWindow.draw(wolfFatPerRabbitValueText);
                Back.draw(mainWindow);
                plus5.draw(mainWindow);
                plus6.draw(mainWindow);
                plus7.draw(mainWindow);
                plus8.draw(mainWindow);
                plus9.draw(mainWindow);
                minus5.draw(mainWindow);
                minus6.draw(mainWindow);
                minus7.draw(mainWindow);
                minus8.draw(mainWindow);
                minus9.draw(mainWindow);

            }

            mainWindow.display();

            Sleep(40);
        }

        if (!isSimRunning && startSim)
        {
            //Resising the mainWindow so it will fit the simulation view
            int windowHeight = islandSize * 10 + 60;
            if (windowHeight < 250)
            {
                windowHeight = 250;
            }
            mainWindow.setSize(sf::Vector2u(islandSize * 10 + 350, windowHeight));

            //updating the view to the new size of the mainWindow
            sf::FloatRect visibleArea(0, 0, islandSize * 10 + 350, windowHeight);
            mainWindow.setView(sf::View(visibleArea));

            //Starting the simulation and changing appropriate variables
            sim1.Start(startRabbitsAmount, startfWolfsAmount, startmWolfsAmount, islandSize);
            time1 = std::chrono::high_resolution_clock::now();
            time2 = std::chrono::high_resolution_clock::now();
            elapsed = time2 - time1;
            frameTime1 = std::chrono::high_resolution_clock::now();
            frameTime2 = std::chrono::high_resolution_clock::now();
            elapsedFrameTime = frameTime2 - frameTime1;
            iter = 0;
            speed = 1;
            isSpeedUnlimited = false;
            isPaused = false;
            isSimRunning = true;
            isCustomHedgeApproved = false;

            customHedge1.Initiate(islandSize);
            drawMode = 4;

            //setting the size of the island view and ocean
            ocean.setSize(sf::Vector2f(islandSize * 10 + 60, islandSize * 10 + 60));
            islandView.setSize(sf::Vector2f(islandSize * 10, islandSize * 10));
        }

        while (isSimRunning)
        {
            //controling the helpWindow while the simulation is running
            while (helpWindow.isOpen() && helpWindow.hasFocus())
            {
                while (helpWindow.pollEvent(event2))
                {
                    if (event2.type == event2.Closed)
                    {
                        helpWindow.close();
                    }
                }
                Sleep(50);
            }
            if(!isSpeedUnlimited)
                Sleep(2);
            //polling events from the mainWindow and adjusting parameters accordingly
            while (mainWindow.pollEvent(event1))
            {
                if (event1.type == event1.Closed)
                {
                    mainWindow.close();
                    return 0;
                }
                if (event1.type == event1.KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) && speed <= 200)
                    speed += 1;
                if (event1.type == event1.KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) && speed > 200)
                    isSpeedUnlimited = true;
                if (event1.type == event1.KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && speed > 200)
                    isSpeedUnlimited = false;
                if (event1.type == event1.KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && speed > 1)
                    speed -= 1;
                if (event1.type == event1.KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H))
                {
                    //opening the helpWindow
                    helpWindow.create(sf::VideoMode(310, 685), "Wolf Island - help", sf::Style::Titlebar | sf::Style::Close);
                    helpWindow.draw(htext1);
                    helpWindow.draw(htext2);
                    helpWindow.draw(htext3);
                    helpWindow.draw(htext4);
                    helpWindow.draw(htext5);
                    helpWindow.draw(htext6);
                    helpWindow.draw(htext7);
                    helpWindow.draw(htext8);
                    helpWindow.draw(htext9);
                    helpWindow.draw(htext10);
                    helpWindow.draw(htext11);
                    helpWindow.draw(htext12);
                    helpWindow.draw(htext13);
                    helpWindow.draw(htext14);
                    helpWindow.draw(htext15);
                    helpWindow.draw(htext16);
                    helpWindow.draw(htext17);

                    rabbitView.setPosition(10, 485);
                    fWolfView.setPosition(10, 505);
                    mWolfView.setPosition(10, 525);
                    helpWindow.draw(rabbitView);
                    helpWindow.draw(fWolfView);
                    helpWindow.draw(mWolfView);
                    helpWindow.display();
                }
                if (event1.type == event1.KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                {
                    speed = 1;
                    isSpeedUnlimited = false;
                }
                if (event1.type == event1.KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                {
                    isPaused = !isPaused;
                    blinkPauseCounter = 0;
                }
                if (event1.type == event1.KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
                {
                    speed = 201;
                    isSpeedUnlimited = true;
                }
                //changing draw mode
                if (event1.type == event1.KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
                {
                    drawMode = 1;
                }
                if (event1.type == event1.KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
                {
                    drawMode = 2;
                }
                if (event1.type == event1.KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
                {
                    drawMode = 3;
                }
                if (event1.type == event1.KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
                {
                    drawMode = 4;
                }
                //drawing rabbits
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !isPaused && drawMode == 1 && sim1.rabbitsAlive < islandSizeSq)
                {
                    sim1.addRabbit(sf::Mouse::getPosition(mainWindow).x / 10 + 3,sf::Mouse::getPosition(mainWindow).y / 10 + 3);
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !isPaused && drawMode == 2 && sim1.fWolfsAlive < islandSizeSq)
                {
                    sim1.addFWolf(sf::Mouse::getPosition(mainWindow).x / 10 + 3, sf::Mouse::getPosition(mainWindow).y / 10 + 3);
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !isPaused && drawMode == 3 && sim1.mWolfsAlive < islandSizeSq)
                {
                    sim1.addMWolf(sf::Mouse::getPosition(mainWindow).x / 10 + 3, sf::Mouse::getPosition(mainWindow).y / 10 + 3);
                }

                //drawing custom hedge
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !isPaused && drawMode == 4)
                {
                    for(int i = -1; i < 2; i++)
                        for(int j = -1; j < 2; j++)
                    customHedge1.setField(3, sf::Mouse::getPosition(mainWindow).x / 10 - 3 + i, sf::Mouse::getPosition(mainWindow).y / 10 - 3 + j);
                }
                if (event1.type == event1.KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
                {
                    if (isHedgeStateChangeAllowed && customHedge1.checkHedge() > 0)
                    {
                        isCustomHedgeApproved = true;
                        isHedgeEnabled = true;
                        isHedgeStateChangeAllowed = false;
                        wasCustomHedgeModified = true;
                    }
                }
                //returning to the main menu
                if (event1.type == event1.KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                {
                    startSim = false;
                    isSimRunning = false;
                    isHedgeEnabled = false;
                    isHedgeStateChangeAllowed = true;
                    sim1.isHedgeGenerated = false;
                    genereateHedgeOnNextClick = false;
                    //Resizing the mainWindow
                    mainWindow.setSize(sf::Vector2u(750, 460));

                    //updating the view to the new size of the mainWindow
                    sf::FloatRect visibleArea(0, 0, 750, 460);
                    mainWindow.setView(sf::View(visibleArea));
                }
            }
            //running the simulation
            if (elapsed.count() > (1 / double(speed)) && (sim1.fWolfsAlive > 0 || sim1.mWolfsAlive > 0 || (sim1.rabbitsAlive < islandSizeSq && sim1.rabbitsAlive > 0)) && !isSpeedUnlimited && !isPaused)
            {
                sim1.run(isHedgeEnabled, customHedge1, wasCustomHedgeModified);
                iter++;
                time1 = std::chrono::high_resolution_clock::now();
                isHedgeStateChangeAllowed = true;
                if (isCustomHedgeApproved)
                {
                    isCustomHedgeApproved = false;
                    customHedge1.clearHedge();
                }
            }
            if ((sim1.fWolfsAlive > 0 || sim1.mWolfsAlive > 0 || (sim1.rabbitsAlive < islandSizeSq && sim1.rabbitsAlive > 0)) && isSpeedUnlimited && !isPaused)
            {
                sim1.run(isHedgeEnabled, customHedge1, wasCustomHedgeModified);
                iter++;
                isHedgeStateChangeAllowed = true;
                if (isCustomHedgeApproved)
                {
                    isCustomHedgeApproved = false;
                    customHedge1.clearHedge();
                }
            }
            if (event1.type == event1.MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && !isPaused && isHedgeStateChangeAllowed && isHedgeEnabled)
            {
                isHedgeEnabled = false;
                isHedgeStateChangeAllowed = false;
            }
            if (event1.type == event1.MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && !isPaused)
            {
                customHedge1.clearHedge();
            }
            //rendering content of the mainWindow
            if (elapsedFrameTime.count() > 0.016667)
            {
                mainWindow.clear();
                sim1.draw(mainWindow, ocean, islandView, rabbitView, fWolfView, mWolfView, font1, isHedgeEnabled);
                if (!isCustomHedgeApproved && drawMode == 4)
                {
                    rabbitView.setFillColor(sf::Color::Blue);
                    for (int i = 0; i < islandSize; i++)
                        for (int j = 0; j < islandSize; j++)
                            if (customHedge1.getField(i, j) == 3)
                            {
                                rabbitView.setPosition(i * 10 + 30, j * 10 + 30);
                                mainWindow.draw(rabbitView);
                            }
                    rabbitView.setFillColor(sf::Color::White);
                }

                std::string str4 = "Iteration: ";
                std::string str5 = "Max Speed: ";
                std::string str6 = "Island Size: ";
                str4 = str4 + std::to_string(iter);
                if(!isSpeedUnlimited)
                    str5 = str5 + std::to_string(speed);
                else
                    str5 = str5 + "Infinite";
                str6 = str6 + std::to_string(islandSize) + "x" + std::to_string(islandSize);
                sf::Text text4;
                sf::Text text5;
                sf::Text text7;
                sf::Text text8;
                sf::Text text10;
                sf::Text text11;
                sf::Text text12;
                text4.setFont(font1);
                text5.setFont(font1);
                text7.setFont(font1);
                text8.setFont(font1);
                text10.setFont(font1);
                text11.setFont(font1);
                text12.setFont(font1);
                text4.setString(str4);
                text5.setString(str5);
                text7.setString("Paused");
                if (isHedgeEnabled)
                    text10.setString("Hedge: Enabled");
                else
                    text10.setString("Hedge: Disabled");
                text11.setString(str6);
                switch (drawMode)
                {
                case 1:
                    text12.setString("Draw Mode: Rabbits");
                    break;
                case 2:
                    text12.setString("Draw Mode: F Wolfs");
                    break;
                case 3:
                    text12.setString("Draw Mode: M Wolfs");
                    break;
                case 4:
                    text12.setString("Draw Mode: Hedge");
                    break;
                }
                text4.setCharacterSize(18);
                text5.setCharacterSize(18);
                text7.setCharacterSize(18);
                text8.setCharacterSize(18);
                text10.setCharacterSize(18);
                text11.setCharacterSize(18);
                text12.setCharacterSize(18);
                text4.setFillColor(sf::Color(255, 255, 255, 255));
                text5.setFillColor(sf::Color(255, 255, 255, 255));
                text7.setFillColor(sf::Color::White);
                text8.setFillColor(sf::Color::White);
                text10.setFillColor(sf::Color::White);
                text11.setFillColor(sf::Color::White);
                text12.setFillColor(sf::Color::White);
                text4.setPosition(islandSize * 10 + 65, 125);
                text5.setPosition(islandSize * 10 + 65, 145);
                text7.setPosition(0,0);
                text10.setPosition(islandSize * 10 + 65, 165);
                text11.setPosition(islandSize * 10 + 65, 185);
                text12.setPosition(islandSize * 10 + 65, 205);
                mainWindow.draw(text4);
                mainWindow.draw(text5);
                mainWindow.draw(text10);
                mainWindow.draw(text11);
                mainWindow.draw(text12);

                //Controling the pause notification
                if (isPaused && blinkPauseCounter >= 30)
                {
                    mainWindow.draw(pauseBackground);
                    mainWindow.draw(text7);
                }
                if (blinkPauseCounter < 60 && isPaused)
                    blinkPauseCounter++;
                if(blinkPauseCounter >= 60 && isPaused)
                    blinkPauseCounter = 0;
                //determining whether the simulation has ended
                if (sim1.rabbitsAlive == 0 && sim1.fWolfsAlive == 0 && sim1.mWolfsAlive == 0) 
                {
                    text8.setPosition(islandSize * 10 + 65, 225);
                    text8.setString("Ecosystem Collapsed");
                    if (blinkSimOverCounter >= 60)
                    {
                        mainWindow.draw(text8);
                    }
                    if (blinkSimOverCounter < 120)
                        blinkSimOverCounter++;
                    else
                        blinkSimOverCounter = 0;
                }
                if (sim1.rabbitsAlive == islandSizeSq && sim1.fWolfsAlive == 0 && sim1.mWolfsAlive == 0)
                {
                    text8.setPosition(islandSize * 10 + 65, 225);
                    text8.setString("Rabbits Dominated\n   The Island");
                    if (blinkSimOverCounter >= 60)
                    {
                        mainWindow.draw(text8);
                    }
                    if (blinkSimOverCounter < 120)
                        blinkSimOverCounter++;
                    else
                        blinkSimOverCounter = 0;
                }
                mainWindow.display();
                frameTime1 = std::chrono::high_resolution_clock::now();
            }
            if (!isSpeedUnlimited)
            {
                time2 = std::chrono::high_resolution_clock::now();
                elapsed = time2 - time1;
            }
            frameTime2 = std::chrono::high_resolution_clock::now();
            elapsedFrameTime = frameTime2 - frameTime1;
        }
    }
    return 0;
}