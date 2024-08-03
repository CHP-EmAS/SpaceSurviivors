#pragma once

#include "GameObject.h"

class Asteroid : public GameObject {
public:
	Asteroid();
	~Asteroid();

	void initializeComponents() override;
	void reinitialize(sf::Vector2f direction, float scale, float speed, float rotationSpeed);
};

