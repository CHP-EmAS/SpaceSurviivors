#pragma once

#include <SFML/Graphics.hpp>

class GraphicService
{
public:
	enum Font {
		Arial,
		Pixel
	};

	enum Texture
	{
		Player,
		Asteroid,
		Bullets,
		Background_0,
		Background_1,
		Background_2,
		Background_3
	};

	virtual const sf::Texture& getTexture(Texture texture) const = 0;
	virtual const sf::Font& getFont(Font font) const = 0;

};

