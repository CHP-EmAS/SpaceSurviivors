#include "Game.h"

#include "SceneManager.h"
#include "Scene.h"
#include "Locator.h"

#include "Asteroid.h"
#include "GameOver.h"

GameScene::GameScene(void) : Scene(Scene::Game)
{
	
}

void GameScene::updateScene(sf::Time deltaTime)
{
	player->update(deltaTime, state);

	if (!state.isGameOver()) {
		enemySpawner.checkSpawnConditions(deltaTime, state, *player);
	} else {
		gameOverTimer += deltaTime.asSeconds();

		if (gameOverTimer >= 4.f) {
			Scene* scene = Locator::getSceneManager().getScene(Scene::GameOver);
			dynamic_cast<GameOverScene*>(scene)->setScore(state.getScore());
			Locator::getSceneManager().changeScene(Scene::GameOver);
		}
	}

	spatialPartitionGrid.updateAll(deltaTime, state);
	bulletPool->updateAll(deltaTime);

	Locator::getSceneManager().setBackgorundReferencePoint(player->getPosition());
}

void GameScene::drawScene(sf::RenderWindow& mainWindow)
{
	bulletPool->drawAll(mainWindow);

	mainWindow.draw(*player);

	spatialPartitionGrid.drawAll(mainWindow);
	
	if (Locator::getSceneManager().debugShowSpatialGrid()) {
		spatialPartitionGrid.debugDraw(mainWindow);
	}

	mainWindow.draw(hud);
}

void GameScene::checkEvents(sf::Event newEvent)
{
	switch (newEvent.type)
	{
	case sf::Event::KeyPressed:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			Locator::getSceneManager().changeScene(Scene::Pause, false);
		}
		break;
	case sf::Event::LostFocus:
		Locator::getSceneManager().changeScene(Scene::Pause, false);
		break;
	}
}

void GameScene::loadScene()
{
	bulletPool = new BulletPool(&spatialPartitionGrid);
	enemySpawner.setSpatialPartitionGrid(&spatialPartitionGrid);

	spatialPartitionGrid.addObserver(&enemySpawner);

	state.addObserver(&enemySpawner);
	state.addObserver(&hud);

	gameOverTimer = 0;
	state.setStartValues();

	player = new Player(bulletPool, &spatialPartitionGrid);
	player->setPosition(sf::Vector2f(WINDOW_SIZE / 2, WINDOW_SIZE / 2));

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
	spatialPartitionGrid.clear();

	state.removeObserver(&enemySpawner);
	state.removeObserver(&hud);

	delete bulletPool;
	bulletPool = nullptr;

	delete player;
	player = nullptr;

	setLoaded(false);
}

GameScene::~GameScene(void)
{
	closeScene();
}
