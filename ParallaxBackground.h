#pragma once

#include <SFML/Graphics.hpp>

class ParallaxBackground : public sf::Drawable
{
public:
	ParallaxBackground();

	void update(const sf::Vector2f referencePosition);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	const float maxOffset1;
	const float maxOffset2;
	const float maxOffset3;

	sf::Sprite background0;
	sf::Sprite background1;
	sf::Sprite background2;
	sf::Sprite background3;
};

