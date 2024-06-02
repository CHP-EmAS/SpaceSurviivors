#pragma once

#include "Scene.h"
#include "DropShadowText.h"

class PauseScene : public Scene
{
public:
	PauseScene();

	void updateScene(sf::Time deltaTime) override;
	void drawScene(sf::RenderWindow& mainWindow) override;
	void checkEvents(sf::Event newEvent) override;
	void loadScene() override;
	void restartScene() override;
	void closeScene() override;

private:

	DropShadowText pauseText;
	DropShadowText infoText;
};

