#pragma once

#include <SFML/Graphics.hpp>

class ProgressBar : public sf::Drawable, public sf::Transformable
{
public:
	ProgressBar();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setProgress(float progress);

private:
	sf::Sprite frame;
	sf::Sprite barBeginn;
	sf::Sprite barMiddle;
	sf::Sprite barEnd;
};

