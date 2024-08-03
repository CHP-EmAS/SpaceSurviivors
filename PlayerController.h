#pragma once
#include "Component.h"

class PlayerController : public Component
{
friend class Player;

public:
	PlayerController(std::shared_ptr<GameObject> parent);

	void onEvent(const Event& event) override;
	void onUpdate(const sf::Time& deltaTime) override;
	
private:
	void playGameOverAnimation(const sf::Time& deltaTime);

	void setFlicker(bool flicker);

	bool isInvincible() const;
	void setInvincibility(sf::Time duration);
	void updateInvincibility(const sf::Time& deltaTime);
	
	void shootBullet(int bulletDamage);
	bool checkCollisions();

	sf::Vector2f bulletSpawnPoint;
	float timeSinceLastShot;

	float invincibleTimer;
	float flickerTimer;
	bool flicker;

	float gameOverExplosionTimer;
};

