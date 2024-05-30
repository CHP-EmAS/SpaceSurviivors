#pragma once

#include <SFML/Graphics.hpp>

#include "GameState.h"

class GameObject;

class Controller
{
public:
	Controller(GameObject* parent);

	virtual void simulate(sf::Time deltaTime, GameState& state);
	void applyForce(sf::Vector2f force);

	void debugDraw(sf::RenderTarget& target);

	void setVelocity(sf::Vector2f velocity);
	void setFriction(float friction);
	void setMaxSpeed(float maxSpeed);

	sf::Vector2f getCurrentVelocity();
	float getFriction();
	float getMaxSpeed();

	virtual ~Controller() = default;
protected:
	GameObject* parentObject;

	sf::Vector2f velocity;
	float maxSpeed;
	float friction;

	sf::Vertex velocityLine[2];
};

