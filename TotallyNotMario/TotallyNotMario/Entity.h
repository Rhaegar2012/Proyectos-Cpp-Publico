#pragma once
#ifndef ENTITY_H
#define ENTITY_H
#include"Enums.h"
#include"Observer.h"
#include"ResourceLoader.h"
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include<map>
using namespace std;


class ItemEntity;

class Entity
{
protected:
	//constants
	const float SPRITE_SCALE_X = 2.0f;
	const float SPRITE_SCALE_Y = 2.0f;
	const bool  SPRITE_SMOOTH = false;
	const float ENTITY_MOVEMENT_SPEED_X = 100.f;
	const float ENTITY_MOVEMENT_SPEED_Y = 250.f;
	const float DELAY_STATE_TIMER = 0.2f;
	const float MAX_FALL_SPEED = 400.f;
	const float ENTITY_ANIMATION_SPEED = .2f;

	//Callbacks
	//Observer for sound system- die sound /squish sound 
	Observer<Entity, Events, SoundFXResourceID>* soundPlayerObserver;
	//Observer for game manager- update score when killing an enemy or getting a coin 
	Observer<Entity, Events, int> *gameManagerObserver;
	


	//Components
	unique_ptr<sf::Texture>texture;
	unique_ptr<sf::Sprite> entitySprite;
	sf::Vector2f position;
	sf::FloatRect boundingBox;
	sf::RectangleShape colliderVisual;
	EntityType type;
	ResourceLoader& resourceLoader = ResourceLoader::instance();

	//state variables
	float positionX;
	float positionY;
	float delayTimer = 0.f;
	int numberOfLives;
	EntityStates pendingState = IDLE;
	bool hasDelayedStateUpdate = false;
	sf::Vector2f entityVelocity;
	bool  isFalling;
	bool  isJumping;
	bool  isDebugging;
	bool  isDead;
	bool  isActive;
	EntityStates currentState;
	sf::Vector2f velocity{ 0.f,0.f };
	sf::Vector2f acceleration{ 0.f,0.f };

	//Animation
	float animationTimer = 0.f;
	int   animationIndex = 0;
	vector<string>currentAnimationCycle;





public:
	Entity(unique_ptr<sf::Texture> spriteTexture, sf::Vector2f initialPosition,Observer<Entity,Events,SoundFXResourceID>*soundObserver);
	void SetSprite(unique_ptr<sf::Sprite> spritePtr);
	void SetPosition(sf::Vector2f newPosition);
	sf::Sprite* GetSprite();
	sf::Vector2f GetPosition();
	sf::FloatRect GetBoundingBox();
	sf::RectangleShape GetColliderVisual();
	sf::Vector2f GetVelocity();
	EntityStates GetCurrentState();
	bool IsFalling();
	bool IsJumping();
	bool IsDead();
	bool IsActive();
	void SetIsFalling(bool falling);
	void SetVelocity(sf::Vector2f velocity);
	void UpdatePhysics(float deltaTime);
	virtual void MoveEntity(sf::Vector2f movementDirection, float deltaTime);
	virtual void ApplyVerticalDirection(sf::Vector2f movementDirection, float deltaTime);
	virtual void ApplyJumpMovement(sf::Vector2f movementDirection, float deltaTime);
	virtual void UpdateCurrentState(EntityStates newState);
	virtual void Collect();
	bool OnCollisionEntry(Entity& collider,float deltaTime);
	EntityType GetEntityType();
	void SetEntityType(EntityType type);
	void Die();
	void CalculateEntityVelocity(float deltaTime, sf::Vector2f initialPosition, sf::Vector2f finalPosition);
	void DelayStateUpdate(EntityStates newState,float delataTime);
	void RunAnimationCycle(float deltaTime);
	void SetObserver(Observer<Entity, Events, int>* observer);
};
#endif

