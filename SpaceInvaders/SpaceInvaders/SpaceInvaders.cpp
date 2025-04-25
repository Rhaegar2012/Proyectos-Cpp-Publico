// SpaceInvaders.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "PLAYER.H"
#include "AlienFleet.h"
#include "Game.h"

//=====================================================
//Constants
//=====================================================
const float INITIAL_POSITION_PLAYER_X = 300;
const float INITIAL_POSITION_PLAYER_Y = 430;
const float INITIAL_POSITION_ALIEN_FLEET_X = 75;
const float INITIAL_POSITION_ALIEN_FLEET_Y  = 100;
const int NUMBER_OF_YELLOW_ALIENS  = 24;
const int NUMBER_OF_RED_ALIENS     = 24;
const int NUMBER_OF_GREEN_ALIENS   = 12;


int main()
{
    //Set up game objects
    Player playerCannon(INITIAL_POSITION_PLAYER_X, INITIAL_POSITION_PLAYER_Y);
    AlienFleet alienFleet(INITIAL_POSITION_ALIEN_FLEET_X, INITIAL_POSITION_ALIEN_FLEET_Y, NUMBER_OF_YELLOW_ALIENS, NUMBER_OF_GREEN_ALIENS, NUMBER_OF_RED_ALIENS);
    alienFleet.InitializeAlienFleet();
    alienFleet.CalculateFleetPositions();
    //Initialize Game Manager
    Game gameManager(alienFleet, playerCannon);
    //Run Game 
    gameManager.Run();
    
    
    
}


