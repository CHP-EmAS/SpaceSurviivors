#include "GameOver.h"
#include "Locator.h"

GameOverScene::GameOverScene() : Scene(GameOver)
{
	sf::Text text = sf::Text("Game Over", Locator::getGraphicService().getFont(GraphicService::Pixel), 55);
	text.setLineSpacing(2);
	text.setFillColor(sf::Color::Red);
	gameoverText.setText(text);
	gameoverText.setOrigin(text.getLocalBounds().width / 2, 0);
	gameoverText.setPosition(WINDOW_SIZE / 2, 200);
	gameoverText.setShadowOffset(5);

	setScore(0);
	text = sf::Text("Score: XXXXXXXX", Locator::getGraphicService().getFont(GraphicService::Pixel), 24);
	scoreText.setText(text);
	scoreText.setOrigin(text.getLocalBounds().width / 2, 0);
	scoreText.setPosition(WINDOW_SIZE / 2, 270);
	scoreText.setShadowOffset(3);

	newGameButton.setPosition(500, 500);
	newGameButton.setScale(1.5, 1.5);
	newGameButton.setSize(sf::Vector2f(200, 50));
	newGameButton.setOrigin(100, 25);
	newGameButton.setText(sf::Text("New Game", Locator::getGraphicService().getFont(GraphicService::Pixel), 20));
}

void GameOverScene::updateScene(sf::Time deltaTime)
{
	newGameButton.update();
}

void GameOverScene::drawScene(sf::RenderWindow& mainWindow)
{
	mainWindow.draw(gameoverText);
	mainWindow.draw(scoreText);

	mainWindow.draw(newGameButton);
}

void GameOverScene::checkEvents(sf::Event newEvent)
{
	switch (newEvent.type)
	{
	case sf::Event::MouseButtonReleased:

		if (newEvent.mouseButton.button != 0) {
			break;
		}

		if (newGameButton.isHovered()) {
			Locator::getSceneManager().changeScene(Scene::Game);
		}

		break;
	}
}

void GameOverScene::loadScene()
{

}

void GameOverScene::restartScene()
{

}

void GameOverScene::closeScene()
{

}

void GameOverScene::setScore(int score)
{
	this->score = score;

	std::string scoreString = std::to_string(score);

	int scoreLength = scoreString.length();
	for (int i = 0; i < (8 - scoreLength); i++) {
		scoreString = "0" + scoreString;
	}

	scoreText.setString("Score: " + scoreString);
}
