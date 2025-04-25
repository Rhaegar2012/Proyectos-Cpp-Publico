#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include<string>
#include<SFML/Graphics.hpp>
#include"Bullet.h"
#include"Entity.h"

using namespace std; 
class Player : public Entity
{
private:
	const string texturePath= "Assets/player.png";
	const string bulletTexture = "Assets/player-bullet.png";
	const float RESET_POSITION_PLAYER_X = 300;
	const float RESET_POSITION_PLAYER_Y = 430;
	const float PLAYER_SPEED = 100.f;
	const float LOWER_MOVEMENT_BOUNDARY = 0.f;
	const float UPPER_MOVEMENT_BOUNDARY = 580.f;
	const float BULLET_OFFSET_X = 25; 
	const float BULLET_OFFSET_Y =-8;
	unique_ptr<Bullet> bullet;
	bool isBulletActive; 
public:
	Player(float positionX, float PositionY);
	void SetPosition(float x, float y);
	sf::Texture GetTexture();
	float* GetPosition();
	void MovePlayer(sf::Vector2f movementDirection,float deltaTime);
	void FireCannon();
	Bullet* GetBullet();
	void SetBulletStatus();
	void ResetPlayer();
	

};
#endif

