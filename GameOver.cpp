#include "GameOver.h"
#include "Locator.h"

GameOverScene::GameOverScene() : Scene(GameOver)
{
	gameoverText.setPosition(WINDOW_SIZE / 2, 200);
	gameoverText.setShadowOffset(5);

	infoText.setShadowOffset(3);

	setScore(0);
	sf::Text text = sf::Text("Your Score: XXXXXXXX", Locator::getGraphicService().getFont(GraphicService::Pixel), 30);
	scoreText.setText(text);
	scoreText.setOrigin(text.getLocalBounds().width / 2, 0);
	scoreText.setPosition(WINDOW_SIZE / 2, 300);
	scoreText.setShadowOffset(4);

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

	highscoreText.setPosition(WINDOW_SIZE / 2, 460);

	switchState(false);
}

void GameOverScene::updateScene(sf::Time deltaTime)
{
	continueButton.update();
}

void GameOverScene::drawScene(sf::RenderWindow& mainWindow)
{
	mainWindow.draw(gameoverText);
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
	sf::Text headline = sf::Text(string, Locator::getGraphicService().getFont(GraphicService::Pixel), 60);
	headline.setLineSpacing(2);
	headline.setFillColor(color);
	gameoverText.setText(headline);
	gameoverText.setOrigin(headline.getLocalBounds().width / 2, 0);
}

void GameOverScene::setInfoText(std::string string, int fontSize, sf::Color color)
{
	sf::Text info = sf::Text(string, Locator::getGraphicService().getFont(GraphicService::Pixel), fontSize);
	info.setFillColor(color);

	infoText.setText(info);
	infoText.setOrigin(info.getLocalBounds().width / 2, 0);
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

	sf::Text highscores = sf::Text(strList, Locator::getGraphicService().getFont(GraphicService::Pixel), 24);
	highscoreText.setText(highscores);
	highscoreText.setOrigin(highscores.getLocalBounds().width / 2, 0);
}
