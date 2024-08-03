#include "Game.h"

#include "SceneManager.h"
#include "Scene.h"
#include "Locator.h"

#include "Asteroid.h"
#include "GameOver.h"

GameScene::GameScene(void) : Scene(Scene::Game)
{
	gameOverTimer = 0;

	gameWorld = std::make_shared<World>();
	gameState = std::make_shared<GameState>();
	collisionGrid = std::make_shared<CollisionGrid>();
	gameObjectFactory = std::make_shared<GameObjectFactory>();

	Locator::provideGlobal(gameWorld);
	Locator::provideGlobal(gameState);
	Locator::provideGlobal(collisionGrid);
	Locator::provideGlobal(gameObjectFactory);
}

void GameScene::updateScene(const sf::Time& deltaTime)
{
	gameState->updateGameTime(deltaTime);
	gameWorld->update(deltaTime);

	if (gameState->isGameOver()) {
		gameOverTimer += deltaTime.asSeconds();

		if (gameOverTimer >= 4.f) {
			Scene* scene = Locator::get<SceneManager>()->getScene(Scene::GameOver);
			dynamic_cast<GameOverScene*>(scene)->setScore(gameState->getScore());
			Locator::get<SceneManager>()->changeScene(Scene::GameOver);
		}
	}
}

void GameScene::drawScene(sf::RenderWindow& mainWindow)
{
	mainWindow.draw(*gameWorld.get());
	mainWindow.draw(hud);

#ifdef _DEBUG
	collisionGrid->debugDraw(mainWindow);
#endif

}

void GameScene::checkEvents(sf::Event newEvent)
{
	switch (newEvent.type)
	{
	case sf::Event::KeyPressed:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			Locator::get<SceneManager>()->changeScene(Scene::Pause, false);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
			gameState->updateGameTime(sf::seconds(10));
		}
		break;
	case sf::Event::LostFocus:
		Locator::get<SceneManager>()->changeScene(Scene::Pause, false);
		break;
	}
}

void GameScene::loadScene()
{
	gameOverTimer = 0;
	gameState->setStartValues();
	gameObjectFactory->prepareObjects();

	gameWorld->initialize();
	
	setLoaded(true);
}

void GameScene::restartScene()
{
	closeScene();
	loadScene();
}

void GameScene::closeScene()
{
	gameWorld->reset();
	gameObjectFactory->clear();
	collisionGrid->clear();
	
	setLoaded(false);
}

GameScene::~GameScene(void)
{
	closeScene();
}
