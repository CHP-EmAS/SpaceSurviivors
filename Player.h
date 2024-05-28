#pragma once

#include "GameObject.h"
#include "BulletPool.h"

class Player : public GameObject
{
public:
	Player(BulletPool* bulletPool);

	void interact(Interaction action, GameObject& interactor) override;

	void update(sf::Time deltaTime) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
private:
	BulletPool* bulletPool;
	sf::Vector2f bulletSpawnPoint;
	float timeSinceLastShot;
	float shootInterval;

	sf::Vertex velocityLine[2];
};

