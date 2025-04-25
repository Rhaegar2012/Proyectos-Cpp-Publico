#pragma once
#ifndef ALIENFLEET_H
#define ALIENFLEET_H
#include<iostream>
#include<string>
#include<vector>
#include<random>
#include<SFML/Graphics.hpp>
#include"Alien.h"



using namespace std;
class AlienFleet
{
private:
	//Constants
	const int	NUMBER_OF_ALIEN_ROWS=5;
	const int	NUMBER_OF_ALIEN_COLUMNS=12;
	const float SPRITE_OFFSET_X = 40; 
	const float SPRITE_OFFSET_Y = 40;
	const int	GREEN_ALIEN_POINTS = 300;
	const int	RED_ALIEN_POINTS = 200;
	const int	YELLOW_ALIEN_POINTS = 100;
	const float HORIZONTAL_MOVEMENT_BOUNDARY_LEFT = 0;
	const float HORIZONTAL_MOVEMENT_BOUNDARY_RIGHT = 750;
	const float VERTICAL_MOVEMENT_BOUNDARY = 480.f;
	const string RED_ALIEN_TEXTURE_PATH	= "Assets/red.png";
	const string YELLOW_ALIEN_TEXTURE_PATH	= "Assets/yellow.png";
	const string GREEN_ALIEN_TEXTURE_PATH  = "Assets/green.png";
	const string SPECIAL_ALIEN_TEXTURE_PATH = "Assets/extra.png";
	
	//State variables
	int remainingAliens;
	float originX;
	float originY;
	int numberOfYellowAliens;
	int numberOfRedAliens;
	int numberOfGreenAliens;
	float fleetHorizontalBoundaryPosition;
	float fleetVerticalBoundaryPosition;
	bool  fleetMovingLeft;
	bool  canShoot;
	int   reloadCounter;
	int   alienSelectionIndex;


	

public: 
	vector<unique_ptr<Alien>> alienFleet;
	
public:
	AlienFleet(float originX, float originY,int yellowAliens, int greenAliens, int redAliens );
	void InitializeAlienFleet();
	float GetFleetSpriteOffsetX();
	float GetFleetSpriteOffsetY();
	void CalculateFleetPositions();
	void RemoveAlienFromFleet();
	int  GetRemainingAliens();
	void MoveFleet(float deltaTime);
	void SetShootStatus();
	bool CanShoot();
	void SelectAlienToAttack();
};

#endif

