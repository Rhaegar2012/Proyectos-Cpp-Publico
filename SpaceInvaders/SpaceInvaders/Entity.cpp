#include "Entity.h"
//=====================================================
//Constructor
//=====================================================
Entity::Entity(float x, float y, string textureFile) 
{
	positionX = x;
	positionY = y;
	textureFilePath = textureFile;
	isActive = true;
	collisionDetected = false;
	
	
}


//=====================================================
//Behaviours
//=====================================================
void Entity::SetSprite(unique_ptr<sf::Sprite> newSprite) 
{
	sprite = move(newSprite);
}

sf::Sprite* Entity::GetSprite() 
{
	return sprite.get();
}

void Entity::SetCollisionBox() 
{
	boundingBox = sprite->getGlobalBounds();
	boundingBox.position.x = positionX;
	boundingBox.position.y = positionY;
}

sf::FloatRect Entity::GetCollisionBox() 
{
	return boundingBox;
}

bool Entity::CheckCollision(sf::FloatRect collisionBox,Entity* collisionEntity) 
{
	if (collisionDetected) 
	{
		return false;
	}
	if (const std::optional intersection = boundingBox.findIntersection(collisionBox)) 
	{
		cout << "Collision detected" << endl;
		collisionDetected = true;
		if (collisionEntity->IsActive()) 
		{
			isActive = false;
			return true;
		}
		
	}
	return false;
}

bool Entity::IsActive() 
{
	return isActive;
}

void Entity:: SetActive() 
{
	isActive = !isActive;
}

void Entity::Die() 
{
	entityLives -= 1;
	SetActive();
}

int Entity::GetRemainingLives() 
{
	return entityLives;
}
