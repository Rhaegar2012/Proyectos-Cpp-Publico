#include "EntityPhysics.h"

EntityPhysics::EntityPhysics()
{
}

void EntityPhysics::ApplyJumpForce(Entity& entity,float deltaTime)
{

	sf::Vector2f currentVelocity = entity.GetVelocity();
	sf::Vector2f newVelocity = { currentVelocity.x,-1.f*JUMP_FORCE };
	entity.SetVelocity(newVelocity);
	entity.UpdatePhysics(deltaTime);
}

void EntityPhysics::ApplyGravity(Entity& entity,float deltaTime)
{
	sf::Vector2f currentVelocity = entity.GetVelocity();
	currentVelocity.y += GRAVITY_SCALE * deltaTime;

	if(currentVelocity.y>MAX_FALL_SPEED)
	{
		currentVelocity.y = MAX_FALL_SPEED;
	}
	entity.SetVelocity(currentVelocity);
}

void EntityPhysics::OnNotify(Entity& entity,Events event,float deltaTime)
{
	switch(event)
	{
		case JUMP_EVENT:
			ApplyJumpForce(entity,deltaTime);
			break;
		default:
			break;
	}
		
}