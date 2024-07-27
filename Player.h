#pragma once

#include "GameState.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();

	void initializeComponents() override;

	void interact(const Event event) override;

	void update(const sf::Time deltaTime, GameState& state) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setInvincibility(sf::Time duration);
	bool isInvincible() const;

	void playGameOverAnimation(sf::Time deltaTime);
	
private:
	bool checkCollisions();

	void updateInvincibility(sf::Time deltaTime);
	void setFlicker(bool flicker);

	void shootBullet(int bulletDamage);

	sf::Vector2f bulletSpawnPoint;
	float timeSinceLastShot;
	
	float invincibleTimer;
	float flickerTimer;
	bool flicker;

	float gameOverExplosionTimer;
};

