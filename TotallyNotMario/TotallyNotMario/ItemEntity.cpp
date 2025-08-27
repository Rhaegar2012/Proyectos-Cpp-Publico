#include "ItemEntity.h"

ItemEntity::ItemEntity(unique_ptr<sf::Texture>defaultTexture,sf::Vector2f initialPosition,Observer<Entity,Events,SoundFXResourceID>*soundObserver):Entity(move(defaultTexture),initialPosition,soundObserver)
{
	type = ITEM;
	currentAnimationCycle = itemAnimationFrames;
}


void ItemEntity::Collect()
{
	isActive = false;
	soundPlayerObserver->OnNotify(*this, COLLECT_EVENT, COIN);
	gameManagerObserver->OnNotify(*this, COLLECT_EVENT, 100);
}

