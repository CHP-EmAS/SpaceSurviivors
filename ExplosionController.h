#pragma once
#include "Component.h"

class ExplosionController : public Component
{
friend class Explosion;

public:
	ExplosionController(std::shared_ptr<GameObject> parent);

	void onUpdate(const sf::Time& deltaTime) override;

private:
	float explosionDuration;
	float explosionTimer;
	float frameInterval;

	short explosionFrame;

};

