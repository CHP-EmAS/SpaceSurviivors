#pragma once

#include "Scene.h"
#include "Button.h"
#include "DropShadowText.h"

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
	void checkForHighscore(int score);
	std::string convertScore(int score);

	DropShadowText gameoverText;
	DropShadowText scoreText;
	DropShadowText infoText;

	Button newGameButton;

	std::string highscoreName;
	int highscore;
	int score;
};

