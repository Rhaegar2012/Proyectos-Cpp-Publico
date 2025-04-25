#pragma once
#ifndef ALIEN_H
#define ALIEN_H
#include<string>
#include<SFML/Graphics.hpp>
#include<iostream>
#include "Entity.h"
#include "Bullet.h"
using namespace std;
class Alien : public Entity
{
private:
	static const float ALIEN_SPEED;
	static const float ALIEN_VERTICAL_SHIFT;
	static const string BULLET_TEXTURE;
	static const float BULLET_OFFSET_X;
	static const float BULLET_OFFSET_Y;
	int   pointsAwarded;
	int   alienFleetIndex; 
	string alienName;
	string texturePath;
	unique_ptr<Bullet> alienBullet;

public:
	Alien(float x, float y, int points,int fleetIndex, string alienName, string texturePath);
	void LoadTexture(); 
	void SetTexturePath();
	void SetPosition(float x, float y);
	float* GetPosition();
	sf::Texture& GetTexture();
	void MoveAlien(sf::Vector2f movementDirection,float deltaTime);
	void Attack();
	int GetScore();
	Bullet* GetBullet();
};
#endif

