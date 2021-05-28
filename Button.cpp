#include "Button.h"

Button::Button(sf::Vector2f sizeButton, sf::Vector2f posButton, sf::Vector2f posText, std::string text, int charSize, sf::Font& font)
{
	caption.setString(text);
	caption.setFillColor(sf::Color::White);
	caption.setFont(font);
	caption.setCharacterSize(charSize);
	caption.setPosition(posText);
	outline.setSize(sizeButton);
	outline.setFillColor(sf::Color::White);
	outline.setPosition(posButton);
	sizeButton.x -= 4;
	sizeButton.y -= 4;
	posButton.x += 2;
	posButton.y += 2;
	button.setSize(sizeButton);
	button.setFillColor(sf::Color::Black);
	button.setPosition(posButton);
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(outline);
	window.draw(button);
	window.draw(caption);
}

bool Button::isCursorOver(sf::RenderWindow& window)
{
	float cursorPosX = sf::Mouse::getPosition(window).x;
	float cursorPosY = sf::Mouse::getPosition(window).y;
	float buttonPosX = outline.getPosition().x;
	float buttonPosY = outline.getPosition().y;
	float buttonPosXAndWidth = buttonPosX + outline.getLocalBounds().width;
	float buttonPosYAndHeight = buttonPosY + outline.getLocalBounds().height;
	if (cursorPosX < buttonPosXAndWidth && cursorPosX > buttonPosX && cursorPosY < buttonPosYAndHeight && cursorPosY > buttonPosY)
	{
		return true;
	}
	return false;
}