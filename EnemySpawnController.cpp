#include "EnemySpawnController.h"
#include "Defines.h"
#include "Asteroid.h"

EnemySpawnController::EnemySpawnController()
{
	enemyAmountTargetValue = 10;
	currentEnemySpawned = 0;

	spawnIntervall = 0.5;
}

void EnemySpawnController::checkSpawnConditions(sf::Time deltaTime, SpatialPartitionGrid& grid, Player& player)
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
			spawnX = -SpatialPartitionGrid::CELL_SIZE + 1;
			break;
		case 3: //BOTTOM
			spawnX = rand() % WINDOW_SIZE;
			spawnX = WINDOW_SIZE + SpatialPartitionGrid::CELL_SIZE - 1;
			break;
		}

		sf::Vector2f spawnPoint = sf::Vector2f(spawnX, spawnY);
		sf::Vector2f direction = player.getPosition() - spawnPoint + sf::Vector2f(rand() % 1000 - 500, rand() % 1000 - 500);

		Asteroid* newAsteroid = new Asteroid(direction, (rand() % 4000 + 1000) / 1000.f, rand() % 300 + 100, rand() % 360);
		newAsteroid->spawOnGrid(&grid, spawnPoint);

		spawnTimer = 0;
	}
}

void EnemySpawnController::onEvent(const GameObject& object, Observable::Event event)
{
	if (object.getType() != GameObject::O_Asteroid) {
		return;
	}

	switch (event) {
	case Observable::GRID_OBJECT_SPAWNED:
		currentEnemySpawned++;
		std::cout << "Enemy spawed" << std::endl;
		break;
	case Observable::GRID_OBJECT_DESPAWNED:
		currentEnemySpawned--;
		std::cout << "Enemy despawed" << std::endl;
		break;
	}
}
