#pragma once
#ifndef UI_MANAGER_H
#define UI_MANAGER_H
#include "Enums.h"
#include "ResourceLoader.h"
#include "UILabel.h"
#include<SFML/Graphics.hpp>
#include<iostream>

using namespace std;

class UIManager
{
	private:
		UIManager();
		
		//singleton reference
		static UIManager* instance_;


		//UI Positions
		const sf::Vector2f POINT_LABEL_POSITION = { 200.f,50.f };
		const sf::Vector2f LIVES_LABEL_POSITION = { 400.f,50.f };
		const sf::Vector2f POINT_VALUE_POSITION = { 250.f,50.f };
		const sf::Vector2f LIVES_VALUE_POSITION = { 250.f,50.f };

		//Components
		ResourceLoader& resourceLoader=ResourceLoader::instance();

		//UI Elements
		UILabel* pointsLabel;
		UILabel* pointsValue;
		UILabel* livesLabel;
		UILabel* livesValue;

		//Containers
		vector<UILabel*> UITags;

	public:
		static UIManager& instance()
		{
			static UIManager* instance = new UIManager();
			return *instance;
		}
		


		



};
#endif

