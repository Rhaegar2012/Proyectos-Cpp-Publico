#pragma once
#ifndef BULLET_H
#define BULLET_H
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include"Entity.h"

using namespace std;

class Bullet:public Entity
{
private:
	const float MOVEMENT_SPEED=90.f;

public:
	Bullet(float x, float y, string spriteTexture);
	sf::Texture GetTexture();
	void MoveBullet(int MovementDirection,float deltaTime);
	void DetectCollision();
	void Destroy();
	float* GetPosition();

};

#endif

