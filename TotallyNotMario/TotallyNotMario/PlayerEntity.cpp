#include "PlayerEntity.h"
PlayerEntity::PlayerEntity(unique_ptr<sf::Texture> defaultTexture,sf::Vector2f initialPosition,Observer<Entity,Events,SoundFXResourceID>*soundObserver):Entity(move(defaultTexture),initialPosition,soundObserver)
{
	currentState = IDLE;
	currentAnimationCycle = playerAnimationCycleIdle;
	animationIndex = 0;
	animationTimer = 0.f;
	positionX = initialPosition.x;
	positionY = initialPosition.y;
	numberOfLives = 3;
}

void PlayerEntity::UpdateCurrentState(EntityStates newState)
{
	if(currentState==JUMPING && newState !=FALLING && newState!=GROUNDED)
	{
		return;
	}
	currentState = newState;
	switch (currentState)
	{
	case IDLE:
		entityVelocity = { 0.f,0.f };
		currentAnimationCycle = playerAnimationCycleIdle;
		break;
	case MOVING:
		currentAnimationCycle = playerAnimationCycleRunning;
		break;
	case JUMPING:
		currentAnimationCycle = playerAnimationCycleJumping;
		break;
	case FALLING:
		currentAnimationCycle = playerAnimationCycleIdle;
		break;
	case GROUNDED:
		entityVelocity = { 0.f,0.f };
		currentAnimationCycle = playerAnimationCycleIdle;
		break;
	case DEAD:
		currentAnimationCycle = playerAnimationCycleDead;
		isDead = true;
		break;
	default:
		break;
	}
}

void PlayerEntity::MoveEntity(sf::Vector2f movementDirection,float deltaTime)
{
	sf::Vector2f  currentVelocity = GetVelocity();
	currentVelocity.x = movementDirection.x * ENTITY_MOVEMENT_SPEED_X;
	SetVelocity(currentVelocity);
	UpdatePhysics(deltaTime);
}

void PlayerEntity::ApplyJumpMovement(sf::Vector2f movementDirection , float deltaTime)
{
	float currentVelocity = movementDirection.y;
	if(currentState==JUMPING)
	{
		
		positionY += movementDirection.y * deltaTime;
		currentVelocity += 3;
		
	}

}

void PlayerEntity::ApplyVerticalDirection(sf::Vector2f movementDirection, float deltaTime)
{
	sf::Vector2f initialPosition = { positionX, positionY };

	// Use a higher speed multiplier for vertical movement to make jumps more responsive
	positionY += movementDirection.y * ENTITY_MOVEMENT_SPEED_Y * deltaTime;
	SetPosition({ positionX, positionY });

	sf::Vector2f finalPosition = { positionX, positionY };
	CalculateEntityVelocity(deltaTime, initialPosition, finalPosition);

	// Check if we should transition to falling state
	if (currentState == JUMPING && movementDirection.y > 0) {
		UpdateCurrentState(FALLING);
	}
}

int PlayerEntity::GetNumberOfLives()
{
	return numberOfLives;
}






