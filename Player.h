#pragma once

#include "GameObject.h"
#include "BulletPool.h"

class Player : public GameObject
{
public:
	Player(BulletPool* bulletPool, SpatialPartitionGrid* grid);

	void interact(Interaction action, GameObject& interactor) override;

	void update(sf::Time deltaTime, GameState& state) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setInvincibility(sf::Time duration);
	bool isInvincible();

	void playGameOverAnimation(sf::Time deltaTime);
	
private:
	bool checkCollisions();

	void updateInvincibility(sf::Time deltaTime);
	void setFlicker(bool flicker);

	void shootBullet(int bulletDamage);

	BulletPool* bulletPool;
	sf::Vector2f bulletSpawnPoint;
	float timeSinceLastShot;
	
	float invincibleTimer;
	float flickerTimer;
	bool flicker;

	float gameOverExplosionTimer;
};

