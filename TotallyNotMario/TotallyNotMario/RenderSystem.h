#pragma once
#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#include"Entity.h"
#include"PlayerEntity.h"
#include"EnemyEntity.h"
#include"ItemEntity.h"
#include"UILabel.h"
#include"UIManager.h"
#include<iostream>
#include<SFML/Graphics.hpp>


using namespace std;

class RenderSystem
{
private:


	sf::RenderWindow gameWindow;
	


	public:

		RenderSystem();
		sf::RenderWindow& GetWindow();
		void Render(vector<Entity> &levelEntities,vector<EnemyEntity*> &enemyEntities,vector<unique_ptr<UILabel>> &UILabels, vector<ItemEntity*> itemEntities,PlayerEntity &playerEntity,sf::RenderWindow&gameWindow);
	
	private:
		void RenderLevelEntities(vector<Entity> &levelEntities,sf::RenderWindow &gameWindow);
		void RenderMobEntities(vector<EnemyEntity*> &enemyEntities,sf::RenderWindow &gameWindow);
		void RenderCharacter(Entity &playerEntity,sf::RenderWindow&gameWindow);
		void RenderItems(vector<ItemEntity*>& itemEntities, sf::RenderWindow& gameWindow);
		void RenderUI(vector<unique_ptr<UILabel>>& UILabels, sf::RenderWindow& gameWindow);
		
		
};
#endif

