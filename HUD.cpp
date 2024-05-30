#include "HUD.h"

//#include <string>

#include "Defines.h"
#include "Locator.h"

HUD::HUD()
{
	scoreFrame.setTexture(Locator::getGraphicService().getTexture(GraphicService::UI_ShortPanel));
	scoreFrame.setOrigin(scoreFrame.getTextureRect().getSize().x, 0);
	scoreFrame.setPosition(WINDOW_SIZE - 20, 20);
	scoreFrame.setScale(1.5, 1.5);

	healthFrame.setTexture(Locator::getGraphicService().getTexture(GraphicService::UI_ShortPanel));
	healthFrame.setPosition(20, 20);
	healthFrame.setScale(1.5, 1.5);

	experienceProgressBar.setOrigin(127, 0);
	experienceProgressBar.setPosition(WINDOW_SIZE / 2, 20);
	experienceProgressBar.setScale(1.5, 1.5);

	scoreText.setFont(Locator::getGraphicService().getFont(GraphicService::Pixel));
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(WINDOW_SIZE - 40, 26);
	scoreText.setCharacterSize(26);
	scoreText.setString("XXXXXXXX");
	scoreText.setOrigin(scoreText.getLocalBounds().width, 0);

	levelText.setFont(Locator::getGraphicService().getFont(GraphicService::Pixel));
	levelText.setFillColor(sf::Color::White);
	levelText.setPosition(WINDOW_SIZE / 2, 26);
	levelText.setCharacterSize(26);
	levelText.setString("Level X");
	levelText.setOrigin(scoreText.getLocalBounds().width / 2, 0);
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(scoreFrame);
	target.draw(scoreText);

	target.draw(healthFrame);

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
	levelText.setString("Level " + std::to_string(level));
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
	}
}
