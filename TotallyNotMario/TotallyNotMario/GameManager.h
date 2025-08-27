#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>
#include<sstream>
#include"ResourceLoader.h"
#include"UIManager.h";
#include"RenderSystem.h"
#include"InputSystem.h"
#include"Entity.h"
#include"EnemyEntity.h"
#include"ItemEntity.h"
#include"SoundPlayer.h"
#include"EntityPhysics.h"
#include"UILabel.h"
using namespace std;

class GameManager:public Observer<Entity,Events,int>
{
	private:
		//Constants 
		const float LEVEL_ORIGIN_X = 150.f;
		const float LEVEL_ORIGIN_Y = 150.f;
		const float TEXTURE_SIZE_X = 32.f;
		const float TEXTURE_SIZE_Y = 32.f;
		const string APP_NAME = "TotallyNotMario";
		const int CHARACTER_SIZE = 22;
		
		//Label text
		const string POINT_LABEL_TEXT = "Points X";
		const string LIVE_LABEL_TEXT = "Lives X";


		//Entity Positions
		const sf::Vector2f INITIAL_PLAYER_POSITION			= { 150.f,182.f };
		const sf::Vector2f INITIAL_ENEMY_POSITION_1			= { 350.f,182.f };
		const sf::Vector2f INITIAL_ENEMY_POSITION_2			= { 550.f,182.f };
		const sf::Vector2f INITIAL_ENEMY_POSITION_3			= { 820.f,182.f };
		const sf::Vector2f FINAL_PATROL_POSITION_ENEMY_1	= { 420.f,182.f };
		const sf::Vector2f FINAL_PATROL_POSITION_ENEMY_2	= { 620.f,182.f };
		const sf::Vector2f FINAL_PATROL_POSITION_ENEMY_3	= { 900.f,182.f };
		const sf::Vector2f COIN_INITIAL_POSITION			= { 150.f,162.f };
		const sf::Vector2f SCORE_TEXT_INITIAL_POSITION		= { 180.f,0.f };
		const sf::Vector2f LIVES_TEXT_INITIAL_POSITION		= {-90.F,0.f };

		
		//State variables
		bool isGameOver;
		int points;
		int lives;
	

		//System references
		ResourceLoader& resourceLoader =ResourceLoader::instance();
		UIManager& UIManager		   =UIManager::instance();
		RenderSystem& renderSystem;
		EntityPhysics& physicsEngine;
		SoundPlayer& soundPlayer;
		sf::RenderWindow gameWindow;
		sf::View gameView;
		InputSystem&  inputSystem;

		//Containers
		vector<Entity> environmentEntities;
		vector<EnemyEntity*> enemyEntities;
		vector<ItemEntity*> itemEntities;
		vector<unique_ptr<UILabel>> UILabels;
		map<string,sf::Texture>textureMapPointer;
		map<string, vector<map<string, int>>>*tileCoordinateMapPointer;

		//Game entities 
		PlayerEntity* player;
		EnemyEntity* enemy_1;
		EnemyEntity* enemy_2;
		EnemyEntity* enemy_3;
		ItemEntity* coin_1;

		//UI Entities 
		sf::Font textFont;
		unique_ptr<UILabel> scoreTextLabel;
		unique_ptr<UILabel> playerLivesTextLabel;
	


	public:
		GameManager(const string& textureMappingPath, const string& tileMappingPath, const string&soundFXMappingPath,  RenderSystem &renderSystem,  InputSystem &inputSystem,EntityPhysics &physicsEngine,SoundPlayer& soundSystem);
		void CreateEntities();
		void RunGame();
		void UpdateGameState(float deltaTime);
		void UpdateUIState(float deltaTime);
		void CheckGameOver();
		bool DetectEnvironmentCollision(PlayerEntity& collider,float deltaTime);
		void UpdateGameScore(int score);
		void OnNotify(Entity& entity, Events event, int scoreValue) override;
	

};
#endif

