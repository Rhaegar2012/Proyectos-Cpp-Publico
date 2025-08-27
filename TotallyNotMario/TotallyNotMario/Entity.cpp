#include "Entity.h"

Entity::Entity(unique_ptr<sf::Texture> textPtr,sf::Vector2f initialPosition,Observer<Entity,Events,SoundFXResourceID>* soundObserver):texture(move(textPtr)),entitySprite(make_unique<sf::Sprite>(*texture)),soundPlayerObserver(soundObserver)
{
	isActive = true;
	position	= initialPosition;
	isJumping	= false;
	isDebugging = false;
	isDead		= false;
	entitySprite->setPosition(position);
	entitySprite->setScale({ SPRITE_SCALE_X,SPRITE_SCALE_Y });
	boundingBox = entitySprite->getGlobalBounds();
	colliderVisual.setPosition(boundingBox.position);
	colliderVisual.setOutlineColor(sf::Color::Green);
	colliderVisual.setOutlineThickness(1.f);
	
}

void Entity::SetSprite(unique_ptr<sf::Sprite> sprite)
{
	entitySprite = move(sprite);
	boundingBox = entitySprite->getGlobalBounds();
	if(isDebugging)
	{
		colliderVisual.setPosition(boundingBox.position);
		colliderVisual.setSize({ boundingBox.size.x,boundingBox.size.y });
		colliderVisual.setOutlineColor(sf::Color::Green);
		colliderVisual.setOutlineThickness(1.f);

	}

}

sf::Sprite* Entity::GetSprite() 
{
	return entitySprite.get();
}

sf::RectangleShape Entity::GetColliderVisual()
{
	return colliderVisual;
}

void Entity::SetPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	entitySprite->setPosition(position);
}

sf::Vector2f Entity::GetPosition()
{
	return position;
}

sf::FloatRect Entity::GetBoundingBox()
{
	return boundingBox;
}

sf::Vector2f Entity::GetVelocity()
{
	return entityVelocity;
}

EntityStates Entity::GetCurrentState()
{
	return currentState;
}

void Entity::UpdatePhysics(float deltaTime)
{
	position.x += entityVelocity.x * deltaTime;
	position.y += entityVelocity.y * deltaTime;

	entitySprite->setPosition(position);
	boundingBox = entitySprite->getGlobalBounds();

}

void Entity::MoveEntity(sf::Vector2f movementDirection,float deltaTime)
{
	//Implementation in children

}

bool Entity::IsFalling()
{
	return isFalling;
}

bool Entity::IsJumping()
{
	return isJumping;
}

bool Entity::IsDead()
{
	return isDead;
}

bool Entity::IsActive()
{
	return isActive;
}

void Entity::SetIsFalling(bool falling)
{
	isFalling = falling;
}


void Entity::Die()
{
	if(isDebugging)
	{
		cout << "I'm dead X__X" << endl;
	}
	if(numberOfLives>0)
	{
		numberOfLives--; 
	}
	UpdateCurrentState(DEAD);
	SetVelocity({ 0.f,0.f });
	soundPlayerObserver->OnNotify(*this, DIE_EVENT, DIE);
	
}

bool Entity::OnCollisionEntry(Entity& collider,float deltaTime)
{
	sf::FloatRect collisionBox = collider.GetBoundingBox();
	sf::Vector2f entityCollisionCenter = { 0.f,0.f };

	if(collider.GetEntityType()==ENEMY)
	{
		entityCollisionCenter = { boundingBox.getCenter().x,boundingBox.getCenter().y };
	}
	else if(collider.GetEntityType()==GROUND ||collider.GetEntityType()==SPIKE ||collider.GetEntityType()==PLATFORM || collider.GetEntityType()==ITEM)
	{
		entityCollisionCenter = { boundingBox.getCenter().x,boundingBox.getCenter().y + boundingBox.size.y / 2 };
	}


	if(collisionBox.contains(entityCollisionCenter))
	{
		EntityType colliderType = collider.GetEntityType();
		switch(colliderType)
		{
			case ITEM:
			if (collider.IsActive())
			{
				collider.Collect();
			}
			break;
			case GROUND:
				if(entityVelocity.x!=0)
				{
					UpdateCurrentState(MOVING);
				}
				else if(entityVelocity.x==0)
				{
					UpdateCurrentState(GROUNDED);
				}
				position.y = collisionBox.position.y - boundingBox.size.y;
				break;
			case SPIKE:
				UpdateCurrentState(GROUNDED);
				Die();
				break;
			case PLATFORM:
				if(isDebugging)
				{
					cout << "Touching Platform" << endl;
				}
				collider.SetIsFalling(true);
				break;
			case ENEMY:
				//Create enemy entity collision logic
				//Player dies if it touches the entity from the sides
				//Entity dies if it player touches it from above
				if(isDebugging)
				{
					cout << "Touching Enemy" << endl;
					cout <<"Player center(Y): " << entityCollisionCenter.y+entityCollisionCenter.y/3 <<"Enemy Center(Y)"<< collisionBox.getCenter().y + collisionBox.getCenter().y / 4 << endl;
					cout << "Player velocity: " << velocity.y << endl;
				}
				if(currentState==FALLING)
				{
					
					collider.Die();
					soundPlayerObserver->OnNotify(*this, JUMP_EVENT, SQUISH);
					
					break;
				}
				else
				{
					if(!collider.IsDead())
					{
						Die();
					}
					break;
				}
				break;
			
			default:
				if (entityVelocity.y > 0) {
					DelayStateUpdate(FALLING, deltaTime);
				}
				break; 
		}
		return true;
	}
	return false;
}

EntityType Entity::GetEntityType()
{
	return type;
}

void Entity::SetEntityType(EntityType entityType)
{
	type = entityType;
}

void Entity::SetVelocity(sf::Vector2f velocity)
{
	entityVelocity = velocity;
}

void Entity::CalculateEntityVelocity(float deltaTime,sf::Vector2f initialPosition, sf::Vector2f finalPosition)
{
	entityVelocity.x = (finalPosition.x - initialPosition.x) / deltaTime;
	entityVelocity.y = (finalPosition.y - initialPosition.y) / deltaTime;
	cout << "Velocity X" << entityVelocity.x << endl;
	cout << "Velocity Y" << entityVelocity.y << endl;
}

void Entity::DelayStateUpdate(EntityStates state, float deltaTime)
{
	if(!hasDelayedStateUpdate)
	{
		delayTimer = 0.f;
		pendingState = state;
		hasDelayedStateUpdate = true;
	}

	delayTimer += deltaTime;
	if (delayTimer >= DELAY_STATE_TIMER) {
		UpdateCurrentState(pendingState);
		hasDelayedStateUpdate = false;
		delayTimer = 0.f;
	}
}

void Entity::UpdateCurrentState(EntityStates newState)
{
	//Implementation in Children
}

void Entity::ApplyJumpMovement(sf::Vector2f movementDirection,float deltaTime)
{
	//Implementation in Children
}

void Entity::Collect()
{
	//Implementation in Children
}

void Entity::ApplyVerticalDirection(sf::Vector2f movementDirection, float deltaTime)
{
	position.y += movementDirection.y * ENTITY_MOVEMENT_SPEED_Y * deltaTime;
	SetPosition({ position.x, position.y });

	// Update bounding box after position change
	boundingBox = entitySprite->getGlobalBounds();
	colliderVisual.setPosition(boundingBox.position);
	colliderVisual.setSize({ boundingBox.size.x, boundingBox.size.y });
}

void Entity::RunAnimationCycle(float deltaTime)
{
	
	
	animationTimer += deltaTime;
	if (animationTimer > ENTITY_ANIMATION_SPEED)
	{
		animationTimer = 0.f;
		animationIndex++;
		if (animationIndex > currentAnimationCycle.size() - 1)
		{
			animationIndex = 0;
		}
	}
	if (animationIndex > currentAnimationCycle.size() - 1)
	{
		animationIndex = currentAnimationCycle.size() - 1;
	}
	string animationFrame = currentAnimationCycle[animationIndex];
	sf::Texture& spriteTexture = resourceLoader.GetAnimationFrame(animationFrame);
	auto newSprite = make_unique<sf::Sprite>(spriteTexture);
	newSprite->setScale({ SPRITE_SCALE_X,SPRITE_SCALE_Y });
	newSprite->setPosition(position);
	SetSprite(move(newSprite));
}


void Entity::SetObserver(Observer<Entity, Events, int>* observer)
{
	gameManagerObserver = observer;
}