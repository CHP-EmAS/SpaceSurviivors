#pragma once

#include "Scene.h"
#include "Button.h"
#include "DropShadowText.h"
#include "TextInput.h"
#include "ScoreBoard.h"

class GameOverScene : public Scene
{
public:
	GameOverScene();

	void updateScene(const sf::Time& deltaTime) override;
	void drawScene(sf::RenderWindow& mainWindow) override;
	void checkEvents(sf::Event newEvent) override;
	void loadScene() override;
	void restartScene() override;
	void closeScene() override;

	void setScore(int score);

private:
	void switchState(bool isHighscore);

	std::string convertScore(int score);

	void setHeadlineText(std::string string, sf::Color color);

	DropShadowText headlineText;
	DropShadowText scoreText;
	DropShadowText infoText;

	ScoreBoard scoreBoard;

	Button continueButton;
	TextInput nameInput;

	int score;
	bool newHighscore;
};

