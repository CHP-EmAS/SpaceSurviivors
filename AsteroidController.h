#pragma once

#include "Component.h"

class AsteroidController : public Component
{

friend class Asteroid;

public:
	AsteroidController(std::shared_ptr<GameObject> parent);

	void onEvent(const Event& event) override;
	void onUpdate(const sf::Time& deltaTime) override;

	void explode();

private:
	float rotationSpeed;

	float currentHitPoints;
	float totalHitPoins;

	float scoreReward;
	float experienceReward;
};

