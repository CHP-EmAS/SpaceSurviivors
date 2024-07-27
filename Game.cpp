#include "Game.h"

#include "SceneManager.h"
#include "Scene.h"
#include "Locator.h"

#include "Asteroid.h"
#include "GameOver.h"

GameScene::GameScene(void) : Scene(Scene::Game)
{
	Locator::provide(&world);
	Locator::provide(&state);
}

void GameScene::updateScene(sf::Time deltaTime)
{
	state.updateGameTime(deltaTime);
	world.update(deltaTime, state);
}

void GameScene::drawScene(sf::RenderWindow& mainWindow)
{
	mainWindow.draw(world);
	mainWindow.draw(hud);

#ifdef _DEBUG
	world.getCollisionLayer().debugDraw(mainWindow);
#endif

}

void GameScene::checkEvents(sf::Event newEvent)
{
	switch (newEvent.type)
	{
	case sf::Event::KeyPressed:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			Locator::getSceneManager().changeScene(Scene::Pause, false);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
			state.updateGameTime(sf::seconds(10));
		}
		break;
	case sf::Event::LostFocus:
		Locator::getSceneManager().changeScene(Scene::Pause, false);
		break;
	}
}

void GameScene::loadScene()
{
	state.addObserver(hud);

	world.initialize(state);

	setLoaded(true);
}

void GameScene::restartScene()
{
	closeScene();
	loadScene();
}

void GameScene::closeScene()
{
	world.reset(state);

	state.removeObserver(hud);

	setLoaded(false);
}

GameState& GameScene::getState()
{
	return state;
}

GameScene::~GameScene(void)
{
	closeScene();
}
