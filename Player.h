#pragma once

#include "GameObject.h"
#include "BulletPool.h"

class Player : public GameObject
{
public:
	Player(BulletPool* bulletPool);

	void interact(Interaction action, GameObject& interactor) override;

	void update(sf::Time deltaTime, GameState& state) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setInvincibility(sf::Time duration);
	bool isInvincible();
	
private:
	bool checkCollisions();

	void updateInvincibility(sf::Time deltaTime);
	void setFlicker(bool flicker);

	BulletPool* bulletPool;
	sf::Vector2f bulletSpawnPoint;
	float timeSinceLastShot;
	
	float invincibleTimer;
	
	float flickerTimer;
	bool flicker;
};

