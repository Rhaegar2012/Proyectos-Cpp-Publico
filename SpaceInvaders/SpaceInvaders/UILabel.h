#pragma once
#ifndef UILABEL_H
#define UILABEL_H
#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>

using namespace std;

class UILabel
{
private:
		string labelText;
		int characterSize;
		sf::Font font;
		sf::Vector2f position;
		unique_ptr<sf::Text> text;
public:
		UILabel(string& labelText, const int characterSize, const sf::Font& font,const sf::Vector2f& position);
		void SetLabelTextObject(unique_ptr<sf::Text> text);
		void UpdateLabelText(string& text);
		void Draw(sf::RenderWindow& window);



};
#endif

