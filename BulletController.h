#pragma once

#include "Component.h"

class BulletController : public Component
{
	friend class Bullet;

public:
	BulletController(std::shared_ptr<GameObject> parent);

	void onUpdate(const sf::Time& deltaTime) override;

private:
	float speed;
	int damage;

	sf::Vector2f direction;

	std::weak_ptr<GameObject> owner;
};

