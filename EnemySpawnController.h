#pragma once

#include "Observer.h"
#include "Player.h"
#include "SpatialPartitionGrid.h"

class EnemySpawnController : public Observer
{
public:
	EnemySpawnController();
	void checkSpawnConditions(sf::Time deltaTime, GameState& state, Player& player);

	void setSpatialPartitionGrid(SpatialPartitionGrid* grid);
	void explodeAllEnemys();

	void reset();

private:
	void onEvent(const Observable::Event event, const Observable::EventInfo info) override;

	int enemyAmountTargetValue;
	int currentEnemySpawned;

	float spawnIntervall;
	float spawnTimer;

	float updateTimer;

	SpatialPartitionGrid* grid;
};

