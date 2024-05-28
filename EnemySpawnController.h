#pragma once

#include "Observer.h"
#include "Player.h"
#include "SpatialPartitionGrid.h"

class EnemySpawnController : public Observer
{
public:
	EnemySpawnController();
	void checkSpawnConditions(sf::Time deltaTime, SpatialPartitionGrid& grid, Player& player);

private:
	void onEvent(const GameObject& object, Observable::Event event) override;

	int enemyAmountTargetValue;
	int currentEnemySpawned;

	float spawnIntervall;
	float spawnTimer;
};

