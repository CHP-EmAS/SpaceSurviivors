#include "EnemySpawnController.h"
#include "Defines.h"
#include "Asteroid.h"
#include "Locator.h"
#include "Event.h"

EnemySpawnController::EnemySpawnController()
{
	enemyAmountTargetValue = 1;
	currentEnemySpawned = 0;
	spawnIntervall = 0.6;
	spawnTimer = 0;
	updateTimer = 0;
}

void EnemySpawnController::explodeAllEnemys()
{
	std::list<std::shared_ptr<GameObject>> objects = Locator::getGameWorld().getCollisionLayer().getAllObjects();
	
	while (objects.size() > 0) {
		auto& object = objects.back();

		if (object->type == O_Asteroid) {
			Asteroid* asteroid = dynamic_cast<Asteroid*>(object.get());
			asteroid->explode();
		}

		objects.pop_back();
	}
}

void EnemySpawnController::reset()
{
	enemyAmountTargetValue = 1;
	currentEnemySpawned = 0;

	spawnIntervall = 0.6;

	spawnTimer = 0;
	updateTimer = 0;

	Locator::getGameWorld().getCollisionLayer().clear();
}

void EnemySpawnController::checkSpawnConditions(sf::Time deltaTime, GameState& state, Player& player)
{
	spawnTimer += deltaTime.asSeconds();
	updateTimer += deltaTime.asSeconds();

	if (currentEnemySpawned < enemyAmountTargetValue && spawnTimer > spawnIntervall) {
		int dir = rand() % 4;
		int spawnX = 0;
		int spawnY = 0;

		switch (dir) {
		case 0: //LEFT
			spawnX = -PartitionedLayer::CELL_SIZE + 1;
			spawnY = rand() % WORLD_SIZE;
			break;
		case 1: //RIGHT
			spawnX = WORLD_SIZE + PartitionedLayer::CELL_SIZE - 1;
			spawnY = rand() % WORLD_SIZE;
			break;
		case 2: //TOP
			spawnX = rand() % WORLD_SIZE;
			spawnY = -PartitionedLayer::CELL_SIZE + 1;
			break;
		case 3: //BOTTOM
			spawnX = rand() % WORLD_SIZE;
			spawnY = WORLD_SIZE + PartitionedLayer::CELL_SIZE - 1;
			break;
		}

		sf::Vector2f asteroidSpawnPoint = sf::Vector2f(spawnX, spawnY);
		sf::Vector2f asteroidDirection = player.getPosition() - asteroidSpawnPoint + sf::Vector2f(rand() % 1000 - 500, rand() % 1000 - 500);
		float asteroidScale = (rand() % 2666 + 666) / 1000.f;
		float asteroidSpeed = rand() % 300 + 100;
		float asteroidRotationSpeed = rand() % 360;

		std::shared_ptr<Asteroid> newAsteroid = Locator::getGameWorld().getGameObjectFactory()
			.acquireAsteroid(asteroidDirection, asteroidScale, asteroidSpeed, asteroidRotationSpeed);

		newAsteroid->spaw(asteroidSpawnPoint, L_Collision);

		spawnTimer = 0;
	}

	if (updateTimer > 5.f) {
		float gameSeconds = state.getGameTime().asSeconds();
		float difficutlyRatio = std::min(gameSeconds / 600.f, 1.f);

		enemyAmountTargetValue = std::max(1, int(100.f * difficutlyRatio));
		spawnIntervall = std::max(0.075f, float(0.6 - 0.525 * difficutlyRatio));

		updateTimer = 0;
	}
}

void EnemySpawnController::onEvent(const Event event)
{
	switch (event.type) {
	case Event::GRID_OBJECT_SPAWNED:
	{
		GameObjectWrapper objectWrapper = std::get<GameObjectWrapper>(event.info);

		if (objectWrapper.ref->type == O_Asteroid) {
			currentEnemySpawned++;
		}
		break;
	}
	case Event::GRID_OBJECT_DESPAWNED:
	case Event::GRID_OBJECT_OUT_OF_BOUNDS:
	{
		GameObjectWrapper objectWrapper = std::get<GameObjectWrapper>(event.info);

		if (objectWrapper.ref->type == O_Asteroid) {
			currentEnemySpawned--;
		}
		break;
	}
	case Event::GAME_OVER:
		explodeAllEnemys();
		break;
	}
}
