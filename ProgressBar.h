#pragma once

#include <SFML/Graphics.hpp>

#include "Frame.h"

class ProgressBar : public sf::Drawable, public sf::Transformable
{
public:
	ProgressBar();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setTexture(const sf::Texture& barTexture);

	void setLength(float length);
	void setProgress(float progress);

private:
	Frame frame;

	float progress;

	sf::Sprite barBeginn;
	sf::Sprite barMiddle;
	sf::Sprite barEnd;
};

