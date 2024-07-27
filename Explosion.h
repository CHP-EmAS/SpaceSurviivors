#pragma once
#include "GameObject.h"

class Explosion : public GameObject
{
public:
	Explosion();
	~Explosion();

	void initializeComponents() override;
	void reinitialize(sf::Time duration, float scale, sf::Color tint = sf::Color::White);

	void update(sf::Time deltaTime, GameState& state) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	float explosionDuration;
	float explosionTimer;
	float frameInterval;

	short explosionFrame;
};

