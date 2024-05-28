#pragma once

#include "GameObject.h"

class Asteroid : public GameObject {
public:
	Asteroid(sf::Vector2f direction, float scale, float speed, float rotationSpeed);
	
	void update(sf::Time deltaTime) override;

	void interact(Interaction action, GameObject& interactor) override;
	void setDirection(sf::Vector2f direction);
private:
	int currentHitPoints;
	int totalHitPoins;
};

