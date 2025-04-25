#include "Alien.h"

const float  Alien::ALIEN_SPEED = 70.f;
const float  Alien::ALIEN_VERTICAL_SHIFT = 5.f;
const string Alien::BULLET_TEXTURE = "Assets/alien-bullet.png";
const float  Alien::BULLET_OFFSET_X = 25;
const float  Alien::BULLET_OFFSET_Y = 8;
//=====================================================
//Constructor
//=====================================================
Alien::Alien(float x, float y, int points,int fleetIndex, string name, string textureFilePath):Entity(x,y,textureFilePath)
{
	positionX = x;
	positionY = y;
	alienFleetIndex = fleetIndex;
	positionArray[0] = positionX;
	positionArray[1] = positionY;
	alienName = name;
	texturePath = textureFilePath;
	entityType = ALIEN;
	alienBullet = nullptr;
	pointsAwarded = points;
	entityLives = 1;
	if(!spriteTexture.loadFromFile(texturePath))
	{
		cerr << "Texture failed to load" << texturePath << endl;
	}
	else 
	{
		cout << "Texture load successfully" << endl;
	}
	unique_ptr<sf::Sprite> alienSprite = make_unique<sf::Sprite>(spriteTexture);
	SetSprite(move(alienSprite));
}

void Alien::SetPosition(float x, float y) 
{
	positionX = x;
	positionY = y;
	positionArray[0] = positionX;
	positionArray[1] = positionY;
}

float* Alien::GetPosition() 
{
	return positionArray;
}

sf::Texture& Alien:: GetTexture() 
{
	return spriteTexture;
}

void Alien::MoveAlien(sf::Vector2f movementDirection,float deltaTime) 
{
	positionX += movementDirection.x * ALIEN_SPEED*deltaTime;
	positionY -= movementDirection.y * ALIEN_VERTICAL_SHIFT;
	positionArray[0] = positionX;
	positionArray[1] = positionY;
}


int Alien::GetScore() 
{
	return pointsAwarded;
}

void Alien::Attack() 
{
	if (!alienBullet) 
	{
		alienBullet = make_unique<Bullet>(positionX + BULLET_OFFSET_X, positionY + BULLET_OFFSET_Y, BULLET_TEXTURE);
	}
}

Bullet* Alien::GetBullet() 
{
	return alienBullet.get();
}