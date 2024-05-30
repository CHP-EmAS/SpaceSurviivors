#include "Controller.h"
#include "GameObject.h"
#include "VectorExtension.h"

Controller::Controller(GameObject* parent)
{
	this->parentObject = parent;

    maxSpeed = 1000.f;
    friction = 1.f;

    velocityLine[0].position = sf::Vector2f(0, 0);
    velocityLine[1].position = sf::Vector2f(0, 0);

    velocityLine[0].color = sf::Color::Red;
}

void Controller::simulate(sf::Time deltaTime, GameState& state)
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

void Controller::debugDraw(sf::RenderTarget& target)
{
    velocityLine[0].position = parentObject->getPosition();
    velocityLine[1].position = velocityLine[0].position + getCurrentVelocity();

    target.draw(velocityLine, 2, sf::Lines);
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
