#pragma once

#include "Scene.h"
#include "Button.h"

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

	sf::Text gameoverText;
	sf::Text scoreText;
	sf::Text infoText;

	Button newGameButton;

	int score;
};

