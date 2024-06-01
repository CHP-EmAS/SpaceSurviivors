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

private:
	void onEvent(const Observable::Event event, const Observable::EventInfo info) override;
	void onLevelUp(int newLevel);

	int enemyAmountTargetValue;
	int currentEnemySpawned;

	float spawnIntervall;
	float spawnTimer;

	SpatialPartitionGrid* grid;
};

