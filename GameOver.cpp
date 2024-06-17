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

	highscoreFrame.setSize(sf::Vector2f(325, 150));
	highscoreFrame.setOrigin(highscoreFrame.getSize() / 2.f);
	highscoreFrame.setScale(1.5, 1.5);
	highscoreFrame.setPosition(500, 500);
	highscoreFrame.setColor(sf::Color(255, 200, 0));

	highscoreText.setFont(Locator::getGraphicService().getFont(GraphicService::Pixel));
	highscoreText.setFontSize(24);
	highscoreText.setPosition(WINDOW_SIZE / 2, 460);

	switchState(false);
}

void GameOverScene::updateScene(sf::Time deltaTime)
{
	continueButton.update();
}

void GameOverScene::drawScene(sf::RenderWindow& mainWindow)
{
	mainWindow.draw(headlineText);
	mainWindow.draw(scoreText);
	
	mainWindow.draw(continueButton);

	if (newHighscore) {
		mainWindow.draw(nameInput);
	} else {
		mainWindow.draw(highscoreFrame);
		mainWindow.draw(highscoreText);
	}

	mainWindow.draw(infoText);
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

		if (continueButton.isHovered()) {
			if (newHighscore) {
				highscore.addHighscore(nameInput.getText(), score);
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

	switchState(highscore.isUnderTopThree(score));
}

void GameOverScene::switchState(bool isHighscore)
{
	newHighscore = isHighscore;
	
	if (isHighscore) {
		setInfoText("Type in your Name", 25, sf::Color::White);
		infoText.setPosition(WINDOW_SIZE / 2, 425);

		setHeadlineText("New Highscore!", sf::Color(255, 205, 0));
		continueButton.setText(sf::Text("Save Highscore", Locator::getGraphicService().getFont(GraphicService::Pixel), 20));
		continueButton.setSize(sf::Vector2f(300, 50));
		continueButton.setOrigin(150, 25);
	} else {
		setInfoText("TOP 3", 32, sf::Color(255, 200, 0));
		infoText.setPosition(WINDOW_SIZE / 2, 400);

		setHighscoresText();

		setHeadlineText("Game Over", sf::Color::Red);
		continueButton.setText(sf::Text("New Game", Locator::getGraphicService().getFont(GraphicService::Pixel), 20));
		continueButton.setSize(sf::Vector2f(200, 50));
		continueButton.setOrigin(100, 25);
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

std::string GameOverScene::convertName(std::string name)
{
	name += ":";

	int nameLength = name.length();
	for (int i = 0; i < (15 - nameLength); i++) {
		name = name + " ";
	}

	return name;
}

void GameOverScene::setHeadlineText(std::string string, sf::Color color)
{
	headlineText.setString(string);
	headlineText.setColor(color);
	headlineText.setOrigin(headlineText.getLocalBounds().width / 2, 0);
}

void GameOverScene::setInfoText(std::string string, int fontSize, sf::Color color)
{
	infoText.setColor(color);
	infoText.setFontSize(fontSize);
	infoText.setString(string);
	infoText.setOrigin(infoText.getLocalBounds().width / 2, 0);
}

void GameOverScene::setHighscoresText()
{
	std::vector<Highscore::Entry> list = highscore.getHighscores();

	std::string strList = "";

	int listSize = std::min(3, (int)list.size());
	for (int i = 0; i < listSize; i++) {
		strList += convertName(list[i].name);
		strList += convertScore(list[i].score);
		strList += "\n\n";
	}

	highscoreText.setString(strList);
	highscoreText.setOrigin(highscoreText.getLocalBounds().width / 2, 0);
}
