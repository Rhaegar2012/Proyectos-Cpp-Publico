#include "Bullet.h"
//=====================================================
//Constructor
//=====================================================
Bullet::Bullet(float x, float y , string texturePath):Entity(x,y,texturePath)
{
	positionX = x;
	positionY = y;
	positionArray[0] = x;
	positionArray[1] = y;
	entityType = BULLET;
	if (!spriteTexture.loadFromFile(texturePath)) 
	{
		cout << "Failed to load bullet texture";
	}
	

}

void Bullet::MoveBullet(int movementDirection,float deltaTime) 
{
	positionY +=movementDirection*MOVEMENT_SPEED*deltaTime;
	positionArray[1] = positionY;
}

void Bullet::DetectCollision() 
{
	//TODO
}

void Bullet::Destroy() 
{
	//TODO
}

sf::Texture Bullet::GetTexture()
{
	return spriteTexture;
}

float* Bullet::GetPosition() 
{
	return positionArray;
}