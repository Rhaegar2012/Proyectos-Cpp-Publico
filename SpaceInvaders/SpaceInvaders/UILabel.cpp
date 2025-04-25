#include "UILabel.h"
//=====================================================
//Constructor
//=====================================================
UILabel::UILabel(string& newLabelText, const int newCharacterSize, const sf::Font& newFont, const sf::Vector2f& newPosition) 
{
	labelText = newLabelText;
	characterSize = newCharacterSize;
	font = newFont;
	position = newPosition;

	sf::Text label(font);
	label.setString(labelText);
	label.setCharacterSize(characterSize);
	label.setFillColor(sf::Color::White);
	label.setPosition(position);

	SetLabelTextObject(make_unique<sf::Text>(label));


}

//=====================================================
//Behaviors
//=====================================================
void UILabel::SetLabelTextObject(unique_ptr<sf::Text>newLabel) 
{
	text = move(newLabel);
}

void UILabel::UpdateLabelText(string& newText)
{
	text->setString(newText);
}

void UILabel::Draw(sf::RenderWindow& window) 
{
	window.draw(*text.get());
}



