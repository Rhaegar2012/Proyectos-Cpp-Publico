#pragma once
#ifndef ENEMY_ENTITY_H
#define ENEMY_ENTITY_H
#include "Entity.h"
#include<cmath>
#include<SFML/Graphics.hpp>
#include<iostream>

using namespace std;

class EnemyEntity:public Entity
{
	private:
		//constants
		const float ENEMY_MOVEMENT_SPEED = 20.f;

		//state variables
		sf::Vector2f initialPatrolPosition;
		sf::Vector2f finalPatrolPosition;
		sf::Vector2f currentPosition;
		sf::Vector2f targetPosition;
		

		//animator
		vector<string>enemyAnimationCycleMove = { "EnemyMoving_1","EnemyMoving_2","EnemyMoving_3","EnemyMoving_4" };
		vector<string>enemyAnimationCycleDead = { "EnemyDead_1" };

	public:
		EnemyEntity(unique_ptr<sf::Texture> defaultTexture, sf::Vector2f initialPosition,Observer<Entity,Events,SoundFXResourceID>* soundObserver);
		void UpdateCurrentState(EntityStates newState);
		void MoveEntity(sf::Vector2f movementDirection,float deltaTime);
		void Patrol(float DeltaTime);
		void SetPatrolPosition(sf::Vector2f targetPatrolPosition);

};
#endif

