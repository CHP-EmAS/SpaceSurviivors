#include "BulletPool.h"

BulletPool::BulletPool(SpatialPartitionGrid* objectGrid)
{
	this->objectGrid = objectGrid;

	firstAvailable = &bullets[0];

	for (int i = 0; i < POOL_SIZE; i++) {
		Bullet* next = nullptr;

		if (i < POOL_SIZE - 1) {
			next = &bullets[i + 1];
		}

		bullets[i].next = next;
		bullets[i].grid = objectGrid;
	}
}

void BulletPool::updateAll(sf::Time deltaTime)
{
	for (int i = 0; i < POOL_SIZE; i++) {
		if (bullets[i].bulletUpdate(deltaTime)) {
			bullets[i].isActive = false;
			bullets[i].next = firstAvailable;
			firstAvailable = &bullets[i];
		}
	}
}

void BulletPool::drawAll(sf::RenderWindow& window)
{
	for (int i = 0; i < POOL_SIZE; i++) {
		if (bullets[i].isActive) {
			window.draw(bullets[i]);
		}
	}
}

Bullet* BulletPool::getNewBullet() {
	if (firstAvailable == nullptr) {
		return &bullets[0];
	}

	Bullet* newBullet = firstAvailable;
	firstAvailable = newBullet->next;

	newBullet->isActive = true;
	return newBullet;
}
