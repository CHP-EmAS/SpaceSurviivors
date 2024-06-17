#include "EnemySpawnController.h"
#include "Defines.h"
#include "Asteroid.h"

EnemySpawnController::EnemySpawnController()
{
	enemyAmountTargetValue = 10;
	currentEnemySpawned = 0;

	spawnIntervall = 0.5;
	spawnTimer = 0;
}

void EnemySpawnController::setSpatialPartitionGrid(SpatialPartitionGrid* grid)
{
	this->grid = grid;
}

void EnemySpawnController::explodeAllEnemys()
{
	std::vector<GameObject*> objects = grid->getAllObjects();
	std::cout << "Explode All!" << std::endl;

	while (objects.size() > 0) {
		GameObject* object = objects.back();

		if (object->getType() == GameObject::O_Asteroid) {
			Asteroid* asteroid = dynamic_cast<Asteroid*>(object);
			asteroid->explode();
		}

		objects.pop_back();
	}
}

void EnemySpawnController::checkSpawnConditions(sf::Time deltaTime, GameState& state, Player& player)
{
	spawnTimer += deltaTime.asSeconds();

	if (currentEnemySpawned < enemyAmountTargetValue && spawnTimer > spawnIntervall) {
		int dir = rand() % 4;
		int spawnX = 0;
		int spawnY = 0;

		switch (dir) {
		case 0: //LEFT
			spawnX = -SpatialPartitionGrid::CELL_SIZE + 1;
			spawnY = rand() % WINDOW_SIZE;
			break;
		case 1: //RIGHT
			spawnX = WINDOW_SIZE + SpatialPartitionGrid::CELL_SIZE - 1;
			spawnY = rand() % WINDOW_SIZE;
			break;
		case 2: //TOP
			spawnX = rand() % WINDOW_SIZE;
			spawnY = -SpatialPartitionGrid::CELL_SIZE + 1;
			break;
		case 3: //BOTTOM
			spawnX = rand() % WINDOW_SIZE;
			spawnY = WINDOW_SIZE + SpatialPartitionGrid::CELL_SIZE - 1;
			break;
		}

		sf::Vector2f spawnPoint = sf::Vector2f(spawnX, spawnY);
		sf::Vector2f direction = player.getPosition() - spawnPoint + sf::Vector2f(rand() % 1000 - 500, rand() % 1000 - 500);

		Asteroid* newAsteroid = new Asteroid(direction, (rand() % 4000 + 1000) / 1000.f, rand() % 300 + 100, rand() % 360);
		newAsteroid->spawOnGrid(grid, spawnPoint);

		spawnTimer = 0;
	}
}

void EnemySpawnController::onEvent(const Observable::Event event, const Observable::EventInfo info)
{
	switch (event) {
	case Observable::GRID_OBJECT_SPAWNED:
		if (info.object->getType() == GameObject::O_Asteroid) {
			currentEnemySpawned++;
		}
		break;
	case Observable::GRID_OBJECT_DESPAWNED:
		if (info.object->getType() == GameObject::O_Asteroid) {
			currentEnemySpawned--;
		}
		break;
	case Observable::LEVEL_UPDATED:
		onLevelUp(info.value);
		break;
	case Observable::GAME_OVER:
		explodeAllEnemys();
		break;
	}
}

void EnemySpawnController::onLevelUp(int newLevel)
{
	if (newLevel > 25) {
		enemyAmountTargetValue = 2000;
		spawnIntervall = 0.075;
	}

	enemyAmountTargetValue = std::min((int)std::floor(std::pow(1.5, newLevel)), 1000);
	spawnIntervall = std::max(0.6 - 0.025 * newLevel, 0.075);
}
