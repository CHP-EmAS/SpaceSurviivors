#include "World.h"

#include "Locator.h"
#include "Scene.h"
#include "GameOver.h"
#include "GameObjectFactory.h"

void World::initialize(GameState& state)
{
	objectFactory.prepareObjects();

	enemySpawner.reset();

	collisionLayer.addObserver(objectFactory);
	collisionLayer.addObserver(enemySpawner);
	effectLayer.addObserver(objectFactory);
	effectLayer.addObserver(enemySpawner);

	state.addObserver(enemySpawner);
	
	gameOverTimer = 0;
	state.setStartValues();

	player.reset(new Player());
	player->initializeComponents();
	player->setPosition(sf::Vector2f(WORLD_SIZE / 2, WORLD_SIZE / 2));

	spawnExperiencePuddle(sf::IntRect(10, 10, 980, 980), 10);
}

void World::reset(GameState& state)
{
	collisionLayer.clearObservers();
	effectLayer.clearObservers();

	collisionLayer.clear();
	effectLayer.clear();

	objectFactory.clear();

	state.removeObserver(enemySpawner);

	player.reset();
}

void World::update(const sf::Time deltaTime, GameState& state)
{
	player->update(deltaTime, state);

	if (!state.isGameOver()) {
		enemySpawner.checkSpawnConditions(deltaTime, state, *player);
	}
	else {
		gameOverTimer += deltaTime.asSeconds();

		if (gameOverTimer >= 4.f) {
			Scene* scene = Locator::getSceneManager().getScene(Scene::GameOver);
			dynamic_cast<GameOverScene*>(scene)->setScore(state.getScore());
			Locator::getSceneManager().changeScene(Scene::GameOver);
		}
	}

	collisionLayer.updateGridObjects(deltaTime, state);
	effectLayer.updateObjects(deltaTime, state);

	background.update(player->getPosition());
}

PartitionedLayer& World::getCollisionLayer()
{
	return collisionLayer;
}

EffectLayer& World::getEffectLayer()
{
	return effectLayer;
}

GameObjectFactory& World::getGameObjectFactory()
{
	return objectFactory;
}

EnemySpawnController& World::getEnemySpawnController()
{
	return enemySpawner;
}

void World::spawnExperiencePuddle(sf::IntRect area, int totalAmount)
{
	for (int i = 0; i < totalAmount; i++) {
		int x = rand() % area.width;
		int y = rand() % area.height;

		x += area.left;
		y += area.top;

		auto experiece = objectFactory.acquireExperience(1);
		experiece->spaw(sf::Vector2f(x, y), L_Collision);
	}
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);

	target.draw(*player, states);

	target.draw(collisionLayer, states);
	target.draw(effectLayer, states);
}
