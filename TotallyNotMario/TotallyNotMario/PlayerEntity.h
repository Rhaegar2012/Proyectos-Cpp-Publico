#pragma once
#ifndef PLAYER_ENTITY_H
#define PLAYER_ENTITY_H
#include<iostream>
#include<SFML/Graphics.hpp>
#include "Entity.h"
#include "Enums.h"
#include "ResourceLoader.h"



using namespace std;


class PlayerEntity:public Entity
{
	private:

		//constants
		const float PLAYER_MOVEMENT_SPEED = 1.f;
		const float PLAYER_ANIMATION_SPEED = .2f;

		


		//Containers
		vector<string> playerAnimationCycleIdle		= {"CharacterIdle_1","CharacterIdle_2"};
		vector<string> playerAnimationCycleRunning	= {"CharacterRunning_1","CharacterRunning_2","CharacterRunning_3"};
		vector<string> playerAnimationCycleJumping	= {"CharacterJumping_1","CharacterJumping_2"};
		vector<string> playerAnimationCycleDead = {"CharacterHit"};
		
	public:
		PlayerEntity(unique_ptr<sf::Texture> defaultTexture,sf::Vector2f initialPosition,Observer<Entity,Events,SoundFXResourceID> *soundObserver);
		void UpdateCurrentState(EntityStates newState) override;
		void MoveEntity(sf::Vector2f movementDirection,float deltaTime) override;
		void ApplyJumpMovement(sf::Vector2f movementDirection, float deltaTime) override;
		void ApplyVerticalDirection(sf::Vector2f movementDirection, float deltaTime) override;
		int GetNumberOfLives();
		
};
#endif

