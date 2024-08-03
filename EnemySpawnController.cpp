#include "EnemySpawnController.h"
#include "Defines.h"
#include "Asteroid.h"
#include "AsteroidController.h"
#include "Locator.h"
#include "Event.h"


EnemySpawnController::EnemySpawnController()
{
	enemyAmountTargetValue = 1;
	currentEnemySpawned = 0;
	spawnIntervall = 0.6;
	spawnTimer = 0;
	updateTimer = 0;

	objSpawned = EventDispatcher::registerHandler(EventType::OBJECT_SPAWNED,
		std::bind(&EnemySpawnController::onObjectSpawned, this, std::placeholders::_1));
	
	objDespawned = EventDispatcher::registerHandler(EventType::OBJECT_DESPAWNED,
		std::bind(&EnemySpawnController::onObjectDespawned, this, std::placeholders::_1));
	
	gameOver = EventDispatcher::registerHandler(EventType::GAME_OVER,
		std::bind(&EnemySpawnController::onGameOver, this, std::placeholders::_1));
}

EnemySpawnController::~EnemySpawnController()
{
	EventDispatcher::unregisterHandler(EventType::OBJECT_SPAWNED, objSpawned);
	EventDispatcher::unregisterHandler(EventType::OBJECT_DESPAWNED, objDespawned);
	EventDispatcher::unregisterHandler(EventType::GAME_OVER, gameOver);
}

void EnemySpawnController::explodeAllEnemys()
{
	std::vector<std::shared_ptr<GameObject>> objects = Locator::get<World>()->getAllObjects();
	
	for (auto& object : objects) {
		if (object->type == O_Asteroid) {
			object->getComponent<AsteroidController>()->explode();
		}
	}
}

void EnemySpawnController::reset()
{
	enemyAmountTargetValue = 1;
	currentEnemySpawned = 0;

	spawnIntervall = 0.6;

	spawnTimer = 0;
	updateTimer = 0;
}

void EnemySpawnController::checkSpawnConditions(sf::Time deltaTime, Player& player)
{
	spawnTimer += deltaTime.asSeconds();
	updateTimer += deltaTime.asSeconds();

	if (currentEnemySpawned < enemyAmountTargetValue && spawnTimer > spawnIntervall) {
		int dir = rand() % 4;
		int spawnX = 0;
		int spawnY = 0;

		switch (dir) {
		case 0: //LEFT
			spawnX = -CollisionGrid::CELL_SIZE + 1;
			spawnY = rand() % WORLD_SIZE;
			break;
		case 1: //RIGHT
			spawnX = WORLD_SIZE + CollisionGrid::CELL_SIZE - 1;
			spawnY = rand() % WORLD_SIZE;
			break;
		case 2: //TOP
			spawnX = rand() % WORLD_SIZE;
			spawnY = -CollisionGrid::CELL_SIZE + 1;
			break;
		case 3: //BOTTOM
			spawnX = rand() % WORLD_SIZE;
			spawnY = WORLD_SIZE + CollisionGrid::CELL_SIZE - 1;
			break;
		}

		sf::Vector2f asteroidSpawnPoint = sf::Vector2f(spawnX, spawnY);
		sf::Vector2f asteroidDirection = player.getPosition() - asteroidSpawnPoint + sf::Vector2f(rand() % 1000 - 500, rand() % 1000 - 500);
		float asteroidScale = (rand() % 2666 + 666) / 1000.f;
		float asteroidSpeed = rand() % 300 + 100;
		float asteroidRotationSpeed = rand() % 360;

		std::shared_ptr<Asteroid> newAsteroid = Locator::get<GameObjectFactory>()
			->acquireAsteroid(asteroidDirection, asteroidScale, asteroidSpeed, asteroidRotationSpeed);

		Locator::get<World>()->spawnObject(newAsteroid, asteroidSpawnPoint);

		spawnTimer = 0;
	}

	if (updateTimer > 5.f) {
		float gameSeconds = Locator::get<GameState>()->getGameTime().asSeconds();
		float difficutlyRatio = std::min(gameSeconds / 600.f, 1.f);

		enemyAmountTargetValue = std::max(1, int(100.f * difficutlyRatio));
		spawnIntervall = std::max(0.075f, float(0.6 - 0.525 * difficutlyRatio));

		updateTimer = 0;
	}
}

void EnemySpawnController::onObjectSpawned(const EventInfo& event)
{
	GameObjectEventInfo objectInfo = std::get<GameObjectEventInfo>(event);

	if (objectInfo.ref->type == O_Asteroid) {
		currentEnemySpawned++;
	}
}

void EnemySpawnController::onObjectDespawned(const EventInfo& event)
{
	GameObjectEventInfo objectInfo = std::get<GameObjectEventInfo>(event);

	if (objectInfo.ref->type == O_Asteroid) {
		currentEnemySpawned--;
	}
}

void EnemySpawnController::onGameOver(const EventInfo& event)
{
	explodeAllEnemys();
}
