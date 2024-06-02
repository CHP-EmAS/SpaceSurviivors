#pragma once

#include <SFML/Graphics.hpp>

class Frame : public sf::Drawable, public sf::Transformable
{
public:
	Frame();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setSize(sf::Vector2f size);
	void setColor(sf::Color newColor);

	sf::Vector2f getSize();

private:
	sf::Vector2f size;

	sf::Sprite corners[4];
	sf::Sprite edges[4];
	sf::Sprite base;
};

