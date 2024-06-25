#pragma once

#include "Scene.h"
#include "Button.h"
#include "DropShadowText.h"
#include "TextInput.h"

class GameOverScene : public Scene
{
public:
	GameOverScene();

	void updateScene(sf::Time deltaTime) override;
	void drawScene(sf::RenderWindow& mainWindow) override;
	void checkEvents(sf::Event newEvent) override;
	void loadScene() override;
	void restartScene() override;
	void closeScene() override;

	void setScore(int score);

private:
	void switchState(bool isHighscore);

	std::string convertScore(int score);
	std::string convertName(std::string name);

	void setHeadlineText(std::string string, sf::Color color);
	void setInfoText(std::string string, int fontSize, sf::Color color);
	void setHighscoresText();

	DropShadowText headlineText;
	DropShadowText scoreText;
	DropShadowText infoText;

	Frame highscoreFrame;
	DropShadowText highscoreText;

	Button continueButton;
	TextInput nameInput;

	int score;
	bool newHighscore;
};

