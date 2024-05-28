#include "Controller.h"
#include "GameObject.h"
#include "VectorExtension.h"

Controller::Controller(GameObject* parent)
{
	this->parentObject = parent;

    maxSpeed = 1000.f;
    friction = 1.f;
}

void Controller::simulate(sf::Time deltaTime)
{
    if (velocity != sf::Vector2f(0, 0)) {
        if (std::sqrt(VectorExtension::vectorSquareLength(velocity)) > maxSpeed)
        {
            float angle = std::atan2(velocity.y, velocity.x);
            velocity.x = maxSpeed * std::cos(angle);
            velocity.y = maxSpeed * std::sin(angle);
        }

        velocity *= std::powf(friction, deltaTime.asSeconds());

        parentObject->move(velocity * deltaTime.asSeconds());
    }
}

void Controller::applyForce(sf::Vector2f force)
{
	velocity += force;
}

void Controller::setVelocity(sf::Vector2f velocity)
{
    this->velocity = velocity;
}

void Controller::setFriction(float friction)
{
    this->friction = friction;
}

void Controller::setMaxSpeed(float maxSpeed)
{
    this->maxSpeed = maxSpeed;
}

sf::Vector2f Controller::getCurrentVelocity()
{
    return velocity;
}

float Controller::getFriction()
{
    return friction;
}

float Controller::getMaxSpeed()
{
    return maxSpeed;
}
