#pragma once

#include <SFML/Graphics.hpp>

#include "Frame.h"
#include "DropShadowText.h"

class ScoreBoard : public sf::Drawable, public sf::Transformable
{
public: 
	ScoreBoard();
	
	void refresh();

private:
	Frame highscoreFrame;
	DropShadowText highscoreText;
};

