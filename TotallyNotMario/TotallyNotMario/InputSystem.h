#pragma once
#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H
#include "PlayerEntity.h"
#include "Enums.h"
#include "Observer.h"
#include "EntityPhysics.h"
#include <SFML/Graphics.hpp>
#include<iostream>

class InputSystem
{
	private:
		//Callbacks
		Observer<Entity,Events,float>* physicsEngineObserver;
		Observer<Entity, Events, SoundFXResourceID>* soundPlayerObserver;

	public:
		InputSystem(Observer<Entity,Events,float>* physicsEngineObserver,Observer<Entity,Events,SoundFXResourceID>* soundPlayerObserver);
		void HandlePlayerInput(PlayerEntity& player,float deltaTime); 
		void HandleJumpCommand(PlayerEntity& player, float deltaTime);
};
#endif

