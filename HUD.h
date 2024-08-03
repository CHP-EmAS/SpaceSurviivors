#pragma once

#include "SFML/Graphics.hpp"
#include "GameState.h"
#include "ProgressBar.h"
#include "Frame.h"
#include "DropShadowText.h"
#include "EventDispatcher.h"

class HUD : public sf::Drawable
{
public:
	HUD();
	~HUD();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void updateScore(int score);
	void updateLevel(int level);
	void updateExperienceBar(int experience, int maxExperience);
	void updateHealthBar(int health, int maxHealth);

private:
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

	void onScoreUpdated(const EventInfo& info);
	void onExperienceUpdated(const EventInfo& info);
	void onMaxExperienceUpdated(const EventInfo& info);
	void onLevelUpdated(const EventInfo& info);
	void onHealthUpdated(const EventInfo& info);
	void onMaxHealthUpdated(const EventInfo& info);

	EventHandlerID scoreHandler;
	EventHandlerID experienceHandler;
	EventHandlerID maxExperienceHandler;
	EventHandlerID levelHandler;
	EventHandlerID healthHandler;
	EventHandlerID maxHealthHandler;
};

