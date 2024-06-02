#pragma once

#include "SFML/Graphics.hpp"
#include "Observer.h"
#include "GameState.h"
#include "ProgressBar.h"
#include "Frame.h"
#include "DropShadowText.h"

class HUD : public sf::Drawable, public Observer
{
public:
	HUD();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void updateScore(int score);
	void updateLevel(int level);
	void updateExperienceBar(int experience, int maxExperience);
	void updateHealthBar(int health, int maxHealth);

private:
	void onEvent(const Observable::Event event, const Observable::EventInfo info) override;

	Frame scoreFrame;
	DropShadowText scoreText;

	ProgressBar healthProgressBar;
	DropShadowText healthText;
	
	ProgressBar experienceProgressBar;
	DropShadowText levelText;

	int displayedHealth;
	int displayedMaxHealth;

	int displayedExperience;
	int displayedMaxExperience;	
};

