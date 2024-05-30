#pragma once

#include "SFML/Graphics.hpp"
#include "Observer.h"
#include "GameState.h"
#include "ProgressBar.h"

class HUD : public sf::Drawable, public Observer
{
public:
	HUD();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void updateScore(int score);
	void updateLevel(int level);
	void updateExperienceBar(int experience, int maxExperience);

private:
	void onEvent(const Observable::Event event, const Observable::EventInfo info) override;

	sf::Sprite scoreFrame;
	sf::Text scoreText;

	sf::Sprite healthFrame;

	ProgressBar experienceProgressBar;
	int displayedExperience;
	int displayedMaxExperience;
	sf::Text levelText;
};

