#include "HUD.h"

//#include <string>

#include "Defines.h"
#include "Locator.h"

HUD::HUD()
{
	scoreFrame.setSize(sf::Vector2f(127,30));
	scoreFrame.setOrigin(scoreFrame.getSize().x, 0);
	scoreFrame.setPosition(WINDOW_SIZE - 20, 20);
	scoreFrame.setScale(1.5, 1.5);

	healthProgressBar.setTexture(Locator::getGraphicService().getTexture(GraphicService::UI_RedBar));
	healthProgressBar.setLength(127);
	healthProgressBar.setPosition(20, 20);
	healthProgressBar.setScale(1.5, 1.5);

	experienceProgressBar.setLength(254);
	experienceProgressBar.setOrigin(127, 0);
	experienceProgressBar.setPosition(WINDOW_SIZE / 2, 20);
	experienceProgressBar.setScale(1.5, 1.5);

	scoreText.setString("XXXXXXXX");
	scoreText.setFont(Locator::getGraphicService().getFont(GraphicService::Pixel));
	scoreText.setFontSize(26);
	scoreText.setPosition(WINDOW_SIZE - 40, 26);
	scoreText.setOrigin(scoreText.getLocalBounds().width, 0);
	scoreText.setShadowOffset(2);

	levelText.setString("Level X");
	levelText.setFont(Locator::getGraphicService().getFont(GraphicService::Pixel));
	levelText.setFontSize(26);
	levelText.setPosition(WINDOW_SIZE / 2, 26);
	levelText.setOrigin(levelText.getLocalBounds().width / 2, 0);
	levelText.setShadowOffset(2);

	healthText.setString("X/X HP");
	healthText.setFont(Locator::getGraphicService().getFont(GraphicService::Pixel));
	healthText.setFontSize(26);
	healthText.setPosition(55, 26);
	healthText.setShadowOffset(2);
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(scoreFrame);
	target.draw(scoreText);

	target.draw(healthProgressBar);
	target.draw(healthText);
	
	target.draw(experienceProgressBar);
	target.draw(levelText);
}

void HUD::updateScore(int score)
{
	std::string scoreString = std::to_string(score);

	int scoreLength = scoreString.length();
	for (int i = 0; i < (8 - scoreLength); i++) {
		scoreString = "0" + scoreString;
	}

	scoreText.setString(scoreString);
}

void HUD::updateLevel(int level)
{
	std::string text = "Level " + std::to_string(level);
	levelText.setString(text);
}

void HUD::updateExperienceBar(int experience, int maxExperience)
{
	displayedExperience = experience;
	displayedMaxExperience = maxExperience;
	
	if (maxExperience > 0) {
		experienceProgressBar.setProgress(float(experience) / float(maxExperience));
	} else {
		experienceProgressBar.setProgress(0);
	}
}

void HUD::updateHealthBar(int health, int maxHealth)
{
	displayedHealth = health;
	displayedMaxHealth = maxHealth;

	if (maxHealth > 0) {
		healthProgressBar.setProgress(float(health) / float(maxHealth));
	}
	else {
		healthProgressBar.setProgress(0);
	}

	std::string text = std::to_string(health) + "/" + std::to_string(maxHealth) + " HP";
	healthText.setString(text);
}

void HUD::onEvent(const Observable::Event event, const Observable::EventInfo info)
{
	switch(event) {
	case Observable::SCORE_UPDATED:
		updateScore(info.value);
		break;
	case Observable::EXPERIENCE_UPDATED:
		updateExperienceBar(info.value, displayedMaxExperience);
		break;
	case Observable::MAX_EXPERIENCE_UPDATED:
		updateExperienceBar(displayedExperience, info.value);
		break;
	case Observable::LEVEL_UPDATED:
		updateLevel(info.value);
		break;
	case Observable::HEALTH_UPDATED:
		updateHealthBar(info.value, displayedMaxHealth);
		break;
	case Observable::MAX_HEALTH_UPDATED:
		updateHealthBar(displayedHealth, info.value);
		break;
	}
}
