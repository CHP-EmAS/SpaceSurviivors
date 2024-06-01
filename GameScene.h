#pragma once

#include "Scene.h"

#include "GameState.h"
#include "Player.h"
#include "BulletPool.h"
#include "SpatialPartitionGrid.h"
#include "ParallaxBackground.h"
#include "EnemySpawnController.h"
#include "HUD.h"

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

	~GameScene(void);
private:

	//State
	GameState state;

	//Grid
	SpatialPartitionGrid spatialPartitionGrid;

	//GameObjects
	Player* player;
	BulletPool* bulletPool;

	EnemySpawnController enemySpawner;

	//HUD
	HUD hud;

	float gameOverTimer;
};

