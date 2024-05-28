#pragma once

#include "GameObject.h"
#include "SpatialPartitionGrid.h"

class Bullet : public GameObject
{
	friend class BulletPool;
public:
	Bullet();

	void setOwner(GameObject* owner);
	bool bulletUpdate(sf::Time deltaTime);
private:
	float speed;

	GameObject* shotBy;

	//Pool
	bool isActive;
	Bullet* next;
};

