#pragma once

#include <SFML/System.hpp>

class GameObject;

class Controller
{
public:
	Controller(GameObject* parent);

	virtual void simulate(sf::Time deltaTime);
	void applyForce(sf::Vector2f force);

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
};

