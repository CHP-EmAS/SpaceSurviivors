#pragma once

#include <SFML/Graphics.hpp>

#include "Frame.h"
#include "DropShadowText.h"

class ScoreBoard : public sf::Drawable, public sf::Transformable
{
public: 
	ScoreBoard();
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void refresh();
	
private:
	Frame frame;
	DropShadowText scoresText;
	DropShadowText headlineText;

	std::string convertToEntryText(std::string name, int score);

	void queryHighscoresText();
};

