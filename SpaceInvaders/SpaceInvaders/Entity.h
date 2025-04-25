#pragma once
#ifndef ENTITY_H
#define ENTITY_H
#include<string>
#include<memory>
#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;

enum EntityType 
{
	PLAYER,
	ALIEN,
	BULLET,
	SHIELD
};


class Entity
{
protected:
	sf::Texture spriteTexture;
	unique_ptr<sf::Sprite> sprite;
	sf::FloatRect boundingBox;
	float positionX;
	float positionY;
	float positionArray[2];
	bool isActive;
	bool collisionDetected;
	int entityLives;
	string textureFilePath;
	EntityType entityType;

public:
	Entity(float x, float y, string textureFile);
	void SetSprite(unique_ptr<sf::Sprite>  sprite);
	sf::Sprite* GetSprite();
	void SetCollisionBox();
	sf::FloatRect GetCollisionBox();
	bool CheckCollision(sf::FloatRect collisionBox, Entity* collisionEntity);
	bool IsActive();
	void SetActive();
	void Die();
	int  GetRemainingLives();
};
#endif

