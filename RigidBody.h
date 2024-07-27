#pragma once

#include <SFML/Graphics.hpp>

#include "Component.h"

class RigidBody : public Component {
public:
	RigidBody(std::shared_ptr<GameObject> parent);
	~RigidBody();

	void simulate(sf::Time deltaTime);
	void debugDraw(sf::RenderTarget& target, sf::RenderStates states);

	void applyForce(sf::Vector2f force);

	void setVelocity(sf::Vector2f velocity);
	void setFriction(float friction);
	void setMaxSpeed(float maxSpeed);
	void setBoundingBox(sf::FloatRect box);

	sf::Vector2f getCurrentVelocity() const;
	float getFriction() const;
	float getMaxSpeed() const;

private:
	sf::Vector2f velocity;
	sf::Vector2f lastVelocity;
	sf::Vertex velocityLine[2];

	float maxSpeed;
	float friction;

	sf::FloatRect boundingBox;

	void clipToBoundingBox();
};