#include "GameOver.h"
#include "Locator.h"

GameOverScene::GameOverScene() : Scene(GameOver)
{
	gameoverText.setPosition(WINDOW_SIZE / 2, 200);
	gameoverText.setShadowOffset(5);

	infoText.setPosition(WINDOW_SIZE / 2, 450);
	infoText.setShadowOffset(3);

	setScore(0);
	sf::Text text = sf::Text("Your Score: XXXXXXXX", Locator::getGraphicService().getFont(GraphicService::Pixel), 30);
	scoreText.setText(text);
	scoreText.setOrigin(text.getLocalBounds().width / 2, 0);
	scoreText.setPosition(WINDOW_SIZE / 2, 300);
	scoreText.setShadowOffset(4);

	newGameButton.setPosition(500, 750);
	newGameButton.setScale(1.5, 1.5);
	newGameButton.setSize(sf::Vector2f(200, 50));
	newGameButton.setOrigin(100, 25);
	newGameButton.setText(sf::Text("New Game", Locator::getGraphicService().getFont(GraphicService::Pixel), 20));

	highscoreName = "EmAS";
}

void GameOverScene::updateScene(sf::Time deltaTime)
{
	newGameButton.update();
}

void GameOverScene::drawScene(sf::RenderWindow& mainWindow)
{
	mainWindow.draw(gameoverText);
	mainWindow.draw(scoreText);
	mainWindow.draw(infoText);

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

	

	scoreText.setString("Your Score: " + convertScore(score));

	checkForHighscore(score);
}

void GameOverScene::checkForHighscore(int score)
{
	bool newHighscore = score > highscore;

	sf::Text headline = sf::Text("New Highscore!", Locator::getGraphicService().getFont(GraphicService::Pixel), 60);;
	headline.setLineSpacing(2);
	headline.setFillColor(sf::Color(255, 205, 0));

	sf::Text info = sf::Text("Type in your Name", Locator::getGraphicService().getFont(GraphicService::Pixel), 25);

	if (!newHighscore) {
		headline.setString("Game Over");
		headline.setFillColor(sf::Color::Red);

		info.setString("Highscore by " + highscoreName + ": " + convertScore(highscore));
	}

	gameoverText.setText(headline);
	gameoverText.setOrigin(headline.getLocalBounds().width / 2, 0);

	infoText.setText(info);
	infoText.setOrigin(info.getLocalBounds().width / 2, 0);

	highscore = score;
}

std::string GameOverScene::convertScore(int score)
{
	std::string scoreString = std::to_string(score);

	int scoreLength = scoreString.length();
	for (int i = 0; i < (8 - scoreLength); i++) {
		scoreString = "0" + scoreString;
	}

	return scoreString;
}
