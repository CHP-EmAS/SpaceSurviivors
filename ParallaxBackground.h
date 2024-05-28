#pragma once

#include "Player.h";

class ParallaxBackground : public sf::Drawable
{
public:
	ParallaxBackground();

	void update(const Player& player);
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

