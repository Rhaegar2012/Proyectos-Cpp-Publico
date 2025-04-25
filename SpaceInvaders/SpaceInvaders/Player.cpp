#include <SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include "Player.h"

using namespace std;


//=====================================================
//Constructor
//=====================================================
Player::Player(float x,float y) :Entity(x,y,texturePath)
{
	positionX = x;
	positionY = y;
	positionArray[0] = positionX;
	positionArray[1] = positionY;
	bullet = nullptr;
	entityType = PLAYER;
	entityLives = 3;
	if (!spriteTexture.loadFromFile(texturePath))
	{
		cout << "Failed to load player texture" << texturePath << endl;
	}
	else 
	{
		cout << "Succesfully loaded player texture"<<texturePath << endl;
	}
	
}

//=====================================================
//Behaviors
//=====================================================


void Player::SetPosition(float newX, float newY) 
{
	positionX = newX;
	positionY = newY;
	positionArray[0] = newX;
	positionArray[1] = newY;
	isBulletActive = false;
}

float* Player::GetPosition() 
{
	return positionArray; 
}

Bullet* Player::GetBullet() 
{
	return bullet.get(); 
}

sf::Texture Player::GetTexture() 
{
	return spriteTexture;
}

void Player::MovePlayer(sf::Vector2f movementDirection,float deltaTime)
{
	if(positionX>=LOWER_MOVEMENT_BOUNDARY && positionX<=UPPER_MOVEMENT_BOUNDARY)
	{
		positionX += movementDirection.x * PLAYER_SPEED*deltaTime;
		
	}
	else if (positionX < LOWER_MOVEMENT_BOUNDARY) 
	{
		positionX = LOWER_MOVEMENT_BOUNDARY;
	}
	else if (positionX > UPPER_MOVEMENT_BOUNDARY) 
	{
		positionX = UPPER_MOVEMENT_BOUNDARY;
	}
	positionArray[0] = positionX;
	
	
}

void Player::FireCannon() 
{
	if (bullet == nullptr) 
	{
		bullet = make_unique<Bullet>(positionX + BULLET_OFFSET_X, positionY + BULLET_OFFSET_Y, bulletTexture);
	}
	
}

void Player::SetBulletStatus() 
{
	if (bullet && !bullet->IsActive()) 
	{
		bullet.reset();
	}
}

void Player:: ResetPlayer() 
{
	isActive = true;
	positionX = RESET_POSITION_PLAYER_X;
	positionY = RESET_POSITION_PLAYER_Y;
	positionArray[0] = positionX;
	positionArray[1] = positionY;

}







