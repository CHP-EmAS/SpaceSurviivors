#pragma once

#include "GameObject.h"
#include "SpatialPartitionGrid.h"

class Bullet : public GameObject
{
	friend class BulletPool;
public:
	Bullet();

	void setDamage(int damage);
	void setOwner(GameObject* owner);

	bool bulletUpdate(sf::Time deltaTime);

	int getDamage() { return damage; };
private:
	float speed;
	int damage;

	GameObject* shotBy;

	//Pool
	bool isActive;
	Bullet* next;
};

