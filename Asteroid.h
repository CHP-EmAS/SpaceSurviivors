#pragma once

#include "GameObject.h"

class Asteroid : public GameObject {
public:
	Asteroid();
	~Asteroid();

	void initializeComponents() override;
	void reinitialize(sf::Vector2f direction, float scale, float speed, float rotationSpeed);

	void update(sf::Time deltaTime, GameState& state) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void interact(const Event event) override;

	void explode();
private:
	float rotationSpeed;

	float currentHitPoints;
	float totalHitPoins;

	float scoreReward;
	float experienceReward;
};

