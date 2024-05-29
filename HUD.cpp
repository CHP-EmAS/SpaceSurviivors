#include "HUD.h"

//#include <string>

#include "Defines.h"
#include "Locator.h"

HUD::HUD()
{
	scoreFrame.setTexture(Locator::getGraphicService().getTexture(GraphicService::UI_ScorePanel));
	scoreFrame.setOrigin(scoreFrame.getTextureRect().getSize().x, 0);
	scoreFrame.setPosition(WINDOW_SIZE - 20, 20);
	scoreFrame.setScale(2, 2);

	scoreText.setFont(Locator::getGraphicService().getFont(GraphicService::Pixel));
	scoreText.setFillColor(sf::Color::Cyan);
	scoreText.setPosition(WINDOW_SIZE - 40, 28);
	scoreText.setCharacterSize(34);
	scoreText.setString("00001234");
	scoreText.setOrigin(scoreText.getLocalBounds().width, 0);

}

void HUD::setGameState(GameState* gameState)
{
	this->gameState = gameState;
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(scoreFrame);
	target.draw(scoreText);
}

void HUD::updateScore(int score)
{
	std::string scoreString = std::to_string(score);

	std::cout << scoreString.length() << std::endl;

	int scoreLength = scoreString.length();

	for (int i = 0; i < (8 - scoreLength); i++) {
		scoreString = "0" + scoreString;
	}

	scoreText.setString(scoreString);
}

void HUD::onEvent(const GameObject* object, Observable::Event event)
{
	if (!gameState) return;

	if (event == Observable::GAME_STATE_UPDATED) {
		updateScore(gameState->getScore());
	}
}
