#include "GameOver.h"
#include "Locator.h"

GameOverScene::GameOverScene() : Scene(GameOver)
{
	headlineText.setFont(Locator::getGraphicService().getFont(GraphicService::Pixel));
	headlineText.setFontSize(60);
	headlineText.setPosition(WINDOW_SIZE / 2, 200);
	headlineText.setShadowOffset(5);

	infoText.setFont(Locator::getGraphicService().getFont(GraphicService::Pixel));
	infoText.setShadowOffset(3);
	infoText.setColor(sf::Color::White);
	infoText.setFontSize(25);
	infoText.setString("Type in your Name");
	infoText.setOrigin(infoText.getLocalBounds().width / 2, 0);
	infoText.setPosition(WINDOW_SIZE / 2, 425);

	scoreText.setFont(Locator::getGraphicService().getFont(GraphicService::Pixel));
	scoreText.setFontSize(30);
	scoreText.setPosition(WINDOW_SIZE / 2, 300);
	scoreText.setShadowOffset(4);
	setScore(0);

	continueButton.setPosition(500, 750);
	continueButton.setScale(1.5, 1.5);
	continueButton.setSize(sf::Vector2f(200, 50));
	continueButton.setOrigin(100, 25);
	
	nameInput.setOrigin(nameInput.getSize() / 2.f);
	nameInput.setPosition(500,500);
	nameInput.setScale(1.5, 1.5);

	scoreBoard.setPosition(500, 500);

	switchState(false);
}

void GameOverScene::updateScene(sf::Time deltaTime)
{
	if (newHighscore) {
		bool noName = nameInput.isEmpty();
		if (noName && continueButton.isEnabled()) {
			continueButton.setEnabled(false);
		}
		else if (!noName && !continueButton.isEnabled()) {
			continueButton.setEnabled(true);
		}
	}

	continueButton.update();
}

void GameOverScene::drawScene(sf::RenderWindow& mainWindow)
{
	mainWindow.draw(headlineText);
	mainWindow.draw(scoreText);
	
	mainWindow.draw(continueButton);

	if (newHighscore) {
		mainWindow.draw(nameInput);
		mainWindow.draw(infoText);
	} else {
		mainWindow.draw(scoreBoard);
	}
}

void GameOverScene::checkEvents(sf::Event newEvent)
{
	if (newHighscore) {
		nameInput.checkEvents(newEvent);
	}

	switch (newEvent.type)
	{
	case sf::Event::MouseButtonReleased:

		if (newEvent.mouseButton.button != 0) {
			break;
		}

		if (continueButton.isHovered() && continueButton.isEnabled()) {
			if (newHighscore) {
				Locator::getHighscoreService().submitScore(nameInput.getText(), score);
				nameInput.clear();
				switchState(false);
			}
			else {
				Locator::getSceneManager().changeScene(Scene::Game);
			}
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
	scoreText.setOrigin(scoreText.getLocalBounds().width / 2, 0);

	switchState(Locator::getHighscoreService().isPersonalBest(score));
}

void GameOverScene::switchState(bool isHighscore)
{
	newHighscore = isHighscore;
	
	if (isHighscore) {
		setHeadlineText("New Highscore!", sf::Color(255, 205, 0));
		continueButton.setText(sf::Text("Save Highscore", Locator::getGraphicService().getFont(GraphicService::Pixel), 20));
		continueButton.setSize(sf::Vector2f(300, 50));
		continueButton.setOrigin(150, 25);
		continueButton.setEnabled(false);
	} else {
		setHeadlineText("Game Over", sf::Color::Red);
		continueButton.setText(sf::Text("New Game", Locator::getGraphicService().getFont(GraphicService::Pixel), 20));
		continueButton.setSize(sf::Vector2f(200, 50));
		continueButton.setOrigin(100, 25);
		continueButton.setEnabled(true);

		scoreBoard.refresh();
	}
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

void GameOverScene::setHeadlineText(std::string string, sf::Color color)
{
	headlineText.setString(string);
	headlineText.setColor(color);
	headlineText.setOrigin(headlineText.getLocalBounds().width / 2, 0);
}
