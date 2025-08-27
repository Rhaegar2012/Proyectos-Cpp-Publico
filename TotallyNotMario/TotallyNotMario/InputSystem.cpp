#include "InputSystem.h"
InputSystem::InputSystem(Observer<Entity,Events,float>* physicsObserver,Observer<Entity,Events,SoundFXResourceID>*soundObserver):physicsEngineObserver(physicsObserver),soundPlayerObserver(soundObserver)
{

}

void InputSystem::HandlePlayerInput(PlayerEntity& player,float deltaTime)
{
	sf::Vector2f movementDirection = { 0.f,0.f };
	if(player.GetCurrentState()==FALLING)
	{
		return;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		
		movementDirection = { -1.f,0.f };
		player.UpdateCurrentState(MOVING);
		player.MoveEntity(movementDirection,deltaTime);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			HandleJumpCommand(player, deltaTime);
		}
		
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		
		movementDirection = { 1.f,0.f };
		player.UpdateCurrentState(MOVING);
		player.MoveEntity(movementDirection,deltaTime);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			HandleJumpCommand(player, deltaTime);
		}

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		
		
		HandleJumpCommand(player, deltaTime);
		
	}
	else 
	{
		EntityStates playerCurrentState = player.GetCurrentState();
		switch(playerCurrentState)
		{
			case MOVING:
				player.UpdateCurrentState(IDLE);
				break;
			case JUMPING:
				player.UpdateCurrentState(IDLE);
				break;
			case GROUNDED:
				player.UpdateCurrentState(IDLE);
			default:
				break;
		}
		
	}
	
}

void InputSystem:: HandleJumpCommand(PlayerEntity& player, float deltaTime)
{
 	if(player.GetCurrentState()==JUMPING)
	{
		return;
	}
	player.UpdateCurrentState(JUMPING);
	physicsEngineObserver->OnNotify(player, JUMP_EVENT, deltaTime);
	soundPlayerObserver->OnNotify(player, JUMP_EVENT, JUMP);
		
}
