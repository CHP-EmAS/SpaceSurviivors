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
		ExplosionAnimation,
		Background_0,
		Background_1,
		Background_2,
		Background_3,
		UI_Frame,
		UI_BlueBar,
		UI_RedBar
	};

	virtual const sf::Texture& getTexture(Texture texture) const = 0;
	virtual const sf::Font& getFont(Font font) const = 0;

};

