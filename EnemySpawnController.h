#pragma once

#include "Player.h"
#include "ObjectPool.h"
#include "EventDispatcher.h"

class EnemySpawnController
{
public:
	EnemySpawnController();
	~EnemySpawnController();

	void checkSpawnConditions(sf::Time deltaTime, Player& player);

	void explodeAllEnemys();

	void reset();

private:
	int enemyAmountTargetValue;
	int currentEnemySpawned;

	float spawnIntervall;
	float spawnTimer;

	float updateTimer;

	void onObjectSpawned(const EventInfo& event);
	void onObjectDespawned(const EventInfo& event);
	void onGameOver(const EventInfo& event);

	EventHandlerID objSpawned;
	EventHandlerID objDespawned;
	EventHandlerID gameOver;
};

