#pragma once
#include "GameObject.h"
class Explosion : public GameObject
{
public:
	Explosion(float scale, sf::Time duration);

	void update(sf::Time deltaTime, GameState& state) override;

private:
	float explosionDuration;
	float explosionTimer;
	float frameInterval;

	short explosionFrame;
};

