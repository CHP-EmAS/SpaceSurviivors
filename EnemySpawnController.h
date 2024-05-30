#pragma once

#include "Observer.h"
#include "Player.h"
#include "SpatialPartitionGrid.h"

class EnemySpawnController : public Observer
{
public:
	EnemySpawnController();
	void checkSpawnConditions(sf::Time deltaTime, GameState& state, SpatialPartitionGrid& grid, Player& player);

private:
	void onEvent(const Observable::Event event, const Observable::EventInfo info) override;
	void onLevelUp(int newLevel);

	int enemyAmountTargetValue;
	int currentEnemySpawned;

	float spawnIntervall;
	float spawnTimer;
};

