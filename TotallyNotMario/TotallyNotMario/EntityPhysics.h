#pragma once
#ifndef ENTITY_PHYSICS
#define ENTITY_PHYSICS
#include"Entity.h"
#include"Enums.h"
#include"Observer.h"
#include<iostream>
#include<SFML/Graphics.hpp>
class EntityPhysics:public Observer<Entity,Events,float>
{
	private:
		//constants
		const float GRAVITY_SCALE = 300.f;
		const int JUMP_FORCE = 175.f ;
		const float MAX_FALL_SPEED = 400.f;
	public:
		EntityPhysics();
		void ApplyJumpForce(Entity& entity,float deltaTime);
		void ApplyGravity(Entity& entity,float deltaTime);
	    void OnNotify(Entity& entity, Events event,float deltaTime) override;

};
#endif

