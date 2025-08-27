#include "EnemyEntity.h"

EnemyEntity::EnemyEntity(unique_ptr<sf::Texture> defaultTexture , sf::Vector2f initialPosition,Observer<Entity,Events,SoundFXResourceID>* soundObserver):Entity(move(defaultTexture),initialPosition,soundObserver)
{
	currentState = MOVING;
	type = ENEMY;
	currentAnimationCycle = enemyAnimationCycleMove;
	initialPatrolPosition = initialPosition;
	currentPosition = initialPatrolPosition;
}

void EnemyEntity::SetPatrolPosition(sf::Vector2f targetPatrolPosition)
{
	targetPosition = targetPatrolPosition;
	finalPatrolPosition = targetPatrolPosition;

}

void EnemyEntity::Patrol(float deltaTime)
{
	float distance = abs(currentPosition.x - targetPosition.x);
	if(distance<0.1f)
	{
		if(targetPosition==finalPatrolPosition)
		{
			targetPosition = initialPatrolPosition;
		}
		else if(targetPosition==initialPatrolPosition)
		{
			targetPosition = finalPatrolPosition;
		}
	}
	sf::Vector2f movementDirection = (targetPosition - currentPosition).normalized();
	MoveEntity(movementDirection, deltaTime);

}

void EnemyEntity::MoveEntity(sf::Vector2f movementDirection , float deltaTime)
{
	sf::Vector2f currentVelocity = GetVelocity();
	currentVelocity.x = movementDirection.x * ENEMY_MOVEMENT_SPEED;
	SetVelocity(currentVelocity);
	UpdatePhysics(deltaTime);
	currentPosition = position;
}

void EnemyEntity::UpdateCurrentState(EntityStates newState)
{
	switch(newState)
	{
		case DEAD:
			currentAnimationCycle = enemyAnimationCycleDead;
			isDead = true;
			break;
		case MOVING:
			currentAnimationCycle = enemyAnimationCycleMove;
			break;
	}
}



