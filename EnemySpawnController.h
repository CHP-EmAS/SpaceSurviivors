#pragma once

#include "Observer.h"
#include "Player.h"
#include "ObjectPool.h"

class EnemySpawnController : public Observer
{
public:
	EnemySpawnController();
	void checkSpawnConditions(sf::Time deltaTime, GameState& state, Player& player);

	void explodeAllEnemys();

	void reset();

private:

	int enemyAmountTargetValue;
	int currentEnemySpawned;

	float spawnIntervall;
	float spawnTimer;

	float updateTimer;

	void onEvent(const Event event) override;
};

