#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button
{
	sf::RectangleShape outline;
	sf::RectangleShape button;
	sf::Text caption;
public:
	Button(sf::Vector2f sizeButton, sf::Vector2f posButton, sf::Vector2f posText, std::string text, int charSize, sf::Font& font);
	void draw(sf::RenderWindow& window);
	bool isCursorOver(sf::RenderWindow& window);
};

