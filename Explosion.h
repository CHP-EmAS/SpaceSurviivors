#pragma once
#include "GameObject.h"

class Explosion : public GameObject
{
public:
	Explosion();
	~Explosion();

	void initializeComponents() override;
	void reinitialize(sf::Time duration, float scale, sf::Color tint = sf::Color::White);
};

