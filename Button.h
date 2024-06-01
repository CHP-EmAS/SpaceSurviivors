#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"

class Button : public sf::Drawable, public sf::Transformable
{
public:
	Button();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update();

	void setSize(sf::Vector2f size);
	void setText(sf::Text newText);

	bool isHovered();

private:
	void setColor(sf::Color color);

	sf::Vector2f size;

	sf::Sprite corners[4];
	sf::Sprite edges[4];
	sf::Sprite base;

	sf::Text text;

	Collider collider;
	bool mouseOver;
};

