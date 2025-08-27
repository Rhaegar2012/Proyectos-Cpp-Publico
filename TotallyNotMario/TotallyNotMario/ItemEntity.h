#pragma once
#ifndef ITEM_ENTITY_H
#define ITEM_ENTITY_H
#include "Entity.h"
#include<SFML/Graphics.hpp>
#include<iostream>

using namespace std;

class ItemEntity :public Entity
{
	private:
		vector<string> itemAnimationFrames = {"Coin_1","Coin_2","Coin_3","Coin_4"};
	public:
		ItemEntity(unique_ptr<sf::Texture> defaultTexture, sf::Vector2f initialPosition, Observer<Entity, Events, SoundFXResourceID>* soundObserver);
		void Collect() override;
};

#endif

