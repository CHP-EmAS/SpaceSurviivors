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

	void update(sf::Time deltaTime, GameState& state) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	int getDamage() const { return damage; };
private:
	float speed;
	int damage;

	sf::Vector2f direction;

	std::weak_ptr<GameObject> owner;
};

