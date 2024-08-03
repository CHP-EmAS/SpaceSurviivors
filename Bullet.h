#pragma once

#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();

	void initializeComponents() override;
	void reinitialize(sf::Vector2f direction, int damage);
	
	void shotBy(std::shared_ptr<GameObject> owner);
	int getDamage() const;
};

