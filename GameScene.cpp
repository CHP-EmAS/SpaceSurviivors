#include "GameScene.h"

#include "SceneManager.h"
#include "Scene.h"
#include "Locator.h"

#include "Asteroid.h"

GameScene::GameScene(void) : Scene(Scene::Game)
{
	
}

void GameScene::updateScene(sf::Time deltaTime)
{
	enemySpawner.checkSpawnConditions(deltaTime, spatialPartitionGrid, *player);
	spatialPartitionGrid.updateAll(deltaTime);
	bulletPool->updateAll(deltaTime);
	background.update(*player);
}

void GameScene::drawScene(sf::RenderWindow& mainWindow)
{
	mainWindow.draw(background);
	
	spatialPartitionGrid.drawAll(mainWindow);
	bulletPool->drawAll(mainWindow);

	//spatialPartitionGrid.debugDraw(mainWindow);
}

void GameScene::checkEvents(sf::Event newEvent)
{
	
}

void GameScene::loadScene()
{
	initScene();
	setLoaded(true);
}

void GameScene::restartScene()
{
	closeScene();
	loadScene();
}

void GameScene::closeScene()
{
	spatialPartitionGrid.removeObserver(&enemySpawner);

	delete bulletPool;
	bulletPool = nullptr;

	delete player;
	player = nullptr;

	setLoaded(false);
}

void GameScene::initScene()
{
	bulletPool = new BulletPool(&spatialPartitionGrid);
	player = new Player(bulletPool);

	player->spawOnGrid(&spatialPartitionGrid, sf::Vector2f(WINDOW_SIZE / 2, WINDOW_SIZE / 2));

	spatialPartitionGrid.addObserver(&enemySpawner);
}

GameScene::~GameScene(void)
{
	closeScene();
}
