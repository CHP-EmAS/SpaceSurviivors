#pragma once

#include "GameObject.h"

class Asteroid : public GameObject {
public:
	Asteroid(sf::Vector2f direction, float scale, float speed, float rotationSpeed);
	
	void update(sf::Time deltaTime, GameState& state) override;

	void interact(Interaction action, GameObject& interactor) override;

	void explode();
private:
	float currentHitPoints;
	float totalHitPoins;

	float scoreReward;
	float experienceReward;
};

