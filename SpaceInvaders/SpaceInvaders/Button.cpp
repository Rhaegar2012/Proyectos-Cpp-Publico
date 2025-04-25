#include "Button.h"

//=====================================================
//Constructor
//=====================================================
Button::Button(const sf::Vector2f& size,const sf::Vector2f&position,const sf::Font& newFont, int characterSize, const std::string&text )
{
	shape.setSize(size);
	shape.setPosition(position);
	shape.setFillColor(sf::Color::Blue);
	font = newFont;
	sf::Text label(font);
	SetLabel(make_unique<sf::Text>(label), text, characterSize);



}

//=====================================================
//Behaviors
//=====================================================
void Button::SetLabel(unique_ptr<sf::Text> newLabel , const string&text,const int characterSize)
{
	label = move(newLabel);
	label->setString(text);
	label->setCharacterSize(characterSize);
	label->setPosition({ shape.getPosition().x + shape.getSize().x / 6,shape.getPosition().y + shape.getSize().y / 4 });
	label->setFillColor(sf::Color::White);
}

sf::Text* Button::GetLabel()
{
	return label.get();
}


bool Button:: IsMouseOver(const sf::RenderWindow& window) 
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

bool Button::IsClicked(const sf::RenderWindow& window)
{
	
	if (isClicked && IsMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		cout << "Mouse button clicked"<<endl;
		isClicked = true;
		return true;
	}
	return false;
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(*label.get());
}

void Button::ResetButton() 
{
	isClicked = false;
}



