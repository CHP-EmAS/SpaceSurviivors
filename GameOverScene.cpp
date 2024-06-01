#include "GameOverScene.h"
#include "Locator.h"

GameOverScene::GameOverScene() : Scene(Scene::GameOver)
{
	gameoverText.setString("Game Over");
	gameoverText.setFont(Locator::getGraphicService().getFont(GraphicService::Pixel));
	gameoverText.setCharacterSize(55);
	gameoverText.setLineSpacing(2);
	gameoverText.setFillColor(sf::Color::Red);
	gameoverText.setOrigin(gameoverText.getGlobalBounds().width / 2, 0);
	gameoverText.setPosition(WINDOW_SIZE / 2, 200);

	setScore(0);
	scoreText.setFont(Locator::getGraphicService().getFont(GraphicService::Pixel));
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setOrigin(scoreText.getGlobalBounds().width / 2, 0);
	scoreText.setPosition(WINDOW_SIZE / 2, 270);

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
	gameoverText.setPosition(WINDOW_SIZE / 2 + 3, 203);
	gameoverText.setFillColor(sf::Color::Black);
	mainWindow.draw(gameoverText);

	gameoverText.setPosition(WINDOW_SIZE / 2, 200);
	gameoverText.setFillColor(sf::Color::Red);
	mainWindow.draw(gameoverText);

	scoreText.setPosition(WINDOW_SIZE / 2 + 3, 283);
	scoreText.setFillColor(sf::Color::Black);
	mainWindow.draw(scoreText);

	scoreText.setPosition(WINDOW_SIZE / 2, 280);
	scoreText.setFillColor(sf::Color::White);
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
