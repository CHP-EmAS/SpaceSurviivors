#pragma once

#include "Scene.h"

#include "EventDispatcher.h"
#include "GameState.h"
#include "World.h"
#include "HUD.h"

#include "CircleCollider.h"
#include "BoxCollider.h"

class GameScene : public Scene
{
public:
	GameScene(void);

	void updateScene(const sf::Time& deltaTime);
	void drawScene(sf::RenderWindow& mainWindow);

	void checkEvents(sf::Event newEvent);

	void loadScene();
	void restartScene();
	void closeScene();

	~GameScene(void);

private:
	//World
	std::shared_ptr<World> gameWorld;
	std::shared_ptr<GameState>	gameState;
	std::shared_ptr<CollisionGrid> collisionGrid;
	std::shared_ptr<GameObjectFactory> gameObjectFactory;

	//HUD
	HUD hud;

	float gameOverTimer;
};

