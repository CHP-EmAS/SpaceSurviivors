#pragma once

#include "Scene.h"

#include "GameState.h"
#include "World.h"
#include "HUD.h"

#include "CircleCollider.h"
#include "BoxCollider.h"

class GameScene : public Scene
{
public:
	GameScene(void);

	void updateScene(sf::Time deltaTime);
	void drawScene(sf::RenderWindow& mainWindow);

	void checkEvents(sf::Event newEvent);

	void loadScene();
	void restartScene();
	void closeScene();

	GameState& getState();

	~GameScene(void);
private:

	//State
	GameState state;

	//World
	World world;

	//HUD
	HUD hud;

	sf::Shader fragtest;
	sf::Texture normal;
};

