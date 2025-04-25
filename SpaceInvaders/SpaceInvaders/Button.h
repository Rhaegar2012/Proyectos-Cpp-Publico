#pragma once
#ifndef BUTTON_H
#define BUTTON_H
#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;
class Button
{
	private:
		sf::RectangleShape shape;
		sf::Font font;
		unique_ptr<sf::Text> label;
		bool isClicked = false;

	public:
		Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Font& font,const int characterSize, const std::string& text);
		void SetLabel(unique_ptr<sf::Text> label, const string& text , const int characterSize);
		sf::Text* GetLabel();
		bool IsMouseOver(const sf::RenderWindow& window);
		bool IsClicked(const sf::RenderWindow& window);
		void ResetButton();
		void Draw(sf::RenderWindow& window);
};
#endif

