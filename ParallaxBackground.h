#pragma once

#include <SFML/Graphics.hpp>

class ParallaxBackground : public sf::Drawable
{
public:
	ParallaxBackground();

	void update(const sf::Vector2f referencePosition);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	float maxOffset1;
	float maxOffset2;
	float maxOffset3;

	sf::RectangleShape background0;
	sf::RectangleShape background1;
	sf::RectangleShape background2;
	sf::RectangleShape background3;
};

