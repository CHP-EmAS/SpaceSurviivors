#pragma once

#include "Bullet.h"

class BulletPool
{
public:
	static const int POOL_SIZE = 100;

	BulletPool(SpatialPartitionGrid* objectGrid);

	void updateAll(sf::Time deltaTime);
	void drawAll(sf::RenderWindow& window);

	Bullet* getNewBullet();
private:
	Bullet bullets[POOL_SIZE];
	Bullet* firstAvailable;
	
	SpatialPartitionGrid* objectGrid;
};

