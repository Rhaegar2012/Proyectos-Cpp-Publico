#include "AlienFleet.h"


//=====================================================
//Constructor
//=====================================================
AlienFleet::AlienFleet(float originPointX, float originPointY, int yellowAliens, int greenAliens, int redAliens) 
{
	originX = originPointX;
	originY = originPointY; 
	numberOfYellowAliens = yellowAliens;
	numberOfRedAliens = redAliens;
	numberOfGreenAliens = greenAliens;
	fleetHorizontalBoundaryPosition = originX + (NUMBER_OF_ALIEN_COLUMNS * SPRITE_OFFSET_X);
	fleetVerticalBoundaryPosition   = originY + (NUMBER_OF_ALIEN_ROWS * SPRITE_OFFSET_Y);
	fleetMovingLeft = true;
	canShoot = true;
	alienSelectionIndex = -1;

}

//=====================================================
//Behaviours
//=====================================================
void AlienFleet::InitializeAlienFleet() 
{
	int fleetIndex = 0;
	//Green Aliens
	for (int i = 0; i < numberOfGreenAliens; i++) 
	{
		alienFleet.push_back(make_unique<Alien>(0, 0, GREEN_ALIEN_POINTS, fleetIndex, "green", GREEN_ALIEN_TEXTURE_PATH));
		fleetIndex++;
	}
	//Red Aliens
	for (int i = 0; i < numberOfRedAliens; i++)
	{
		alienFleet.push_back(make_unique<Alien>(0, 0, RED_ALIEN_POINTS, fleetIndex, "red", RED_ALIEN_TEXTURE_PATH));
		fleetIndex++;
	}
	//Yellow Aliens
	for (int i = 0; i < numberOfYellowAliens; i++)
	{
		alienFleet.push_back(make_unique<Alien>(0, 0, YELLOW_ALIEN_POINTS, fleetIndex, "yellow", YELLOW_ALIEN_TEXTURE_PATH));
		fleetIndex++;
	}

}


float AlienFleet::GetFleetSpriteOffsetX() 
{
	return SPRITE_OFFSET_X;
}

void AlienFleet::CalculateFleetPositions() 
{
	int vectorIndex = 0;
	float currentPositionX = originX;
	float currentPositionY = originY;
	for (int i = 0; i < NUMBER_OF_ALIEN_ROWS; i++) 
	{
		for (int j = 0; j < NUMBER_OF_ALIEN_COLUMNS; j++) 
		{
			alienFleet[vectorIndex]->SetPosition(currentPositionX, currentPositionY);
			currentPositionX += SPRITE_OFFSET_X;
			vectorIndex++;
		}
		currentPositionX = originX; 
		currentPositionY += SPRITE_OFFSET_Y;
	}
}

void AlienFleet::MoveFleet(float deltaTime) 
{
	sf::Vector2f movementDirection;
	if (fleetMovingLeft) 
	{
		movementDirection = { -1.f,0.f };
		fleetHorizontalBoundaryPosition += movementDirection.x;
		if (fleetHorizontalBoundaryPosition < HORIZONTAL_MOVEMENT_BOUNDARY_LEFT) 
		{
			fleetMovingLeft = false;
			movementDirection = { 0.f,-1.f };
		}
		
	}
	else 
	{
		movementDirection = { 1.f,0.f };
		fleetHorizontalBoundaryPosition += movementDirection.x;
		if (fleetHorizontalBoundaryPosition > HORIZONTAL_MOVEMENT_BOUNDARY_RIGHT) 
		{
			fleetMovingLeft = true;
			movementDirection = { 0.f,-1.f };
		}
	}
	
	

	for(int i=0;i<alienFleet.size();i++)
	{
		alienFleet[i]->MoveAlien(movementDirection,deltaTime);
	}

}

bool AlienFleet::CanShoot() 
{
	return canShoot;
}

void AlienFleet::SetShootStatus() 
{
	canShoot = !canShoot;
}

void AlienFleet::SelectAlienToAttack() 
{
	vector<int> activeIndices;
	//Gather all indices of active aliens
	for (int i = 0; i < alienFleet.size(); i++) 
	{
		if (alienFleet[i]->IsActive()) 
		{
			activeIndices.push_back(i);
		}

	}
	if (activeIndices.empty()) 
	{
		return;
	}
	//Shuffle the indices
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::shuffle(activeIndices.begin(), activeIndices.end(), gen);
	//Let the first shuffled alien attack
	int selectedIndex = activeIndices.front();
	alienFleet[selectedIndex]->Attack();

}
