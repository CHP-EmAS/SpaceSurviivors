#include "RigidBody.h"

#include <iostream>
#include "Locator.h"
#include "GameObject.h"
#include "VectorExtension.h"

RigidBody::RigidBody(std::shared_ptr<GameObject> parent) : Component(parent)
{
    velocity = sf::Vector2f(0, 0);
    lastVelocity = sf::Vector2f(0, 0);

    maxSpeed = 0;
    friction = 0;
    boundingBox = sf::FloatRect(0, 0, 0, 0);

	debugVelocityLine[0].position = sf::Vector2f(0, 0);
    debugVelocityLine[0].color = sf::Color::Red;
	debugVelocityLine[1].position = sf::Vector2f(0, 0);
}

RigidBody::~RigidBody() {}

void RigidBody::onSimulate(const sf::Time& deltaTime)
{
    if (auto parent = _parent.lock()) {
        if (velocity != sf::Vector2f(0, 0)) {
            if (maxSpeed > 0) {
                if (std::sqrt(vectorSquareLength(velocity)) > maxSpeed)
                {
                    float angle = std::atan2(velocity.y, velocity.x);
                    velocity.x = maxSpeed * std::cos(angle);
                    velocity.y = maxSpeed * std::sin(angle);
                }
            }
       
            if (friction > 0) {
                velocity *= std::powf(friction, deltaTime.asSeconds());
            }
       
            if (std::abs(velocity.x) < std::abs(lastVelocity.x) && std::abs(velocity.x) < 5.f) velocity.x = 0.f;
            if (std::abs(velocity.y) < std::abs(lastVelocity.y) && std::abs(velocity.y) < 5.f) velocity.y = 0.f;

            if (boundingBox.width > 0 && boundingBox.height > 0) {
                clipToBoundingBox();
            }

            lastVelocity = velocity;

            parent->move(velocity * deltaTime.asSeconds());
        }
    }
}

void RigidBody::onDebugDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (Locator::get<SceneManager>()->debugShowVelocity()) {
        if (auto parent = _parent.lock()) {
            debugVelocityLine[0].position = parent->getPosition();
            debugVelocityLine[1].position = debugVelocityLine[0].position + velocity;

            target.draw(debugVelocityLine, 2, sf::Lines);
        }
    }
}

void RigidBody::applyForce(sf::Vector2f force)
{
    velocity += force;
}

void RigidBody::setVelocity(sf::Vector2f velocity)
{
    this->velocity = velocity;
}

void RigidBody::setFriction(float friction)
{
    this->friction = friction;
}

void RigidBody::setMaxSpeed(float maxSpeed)
{
    this->maxSpeed = maxSpeed;
}

void RigidBody::setBoundingBox(sf::FloatRect box)
{
    boundingBox = box;
}

sf::Vector2f RigidBody::getCurrentVelocity() const
{
    return velocity;
}

float RigidBody::getFriction() const
{
    return friction;
}

float RigidBody::getMaxSpeed() const
{
    return maxSpeed;
}

void RigidBody::clipToBoundingBox()
{
    if (auto parent = _parent.lock()) {
        sf::Vector2f movePosition = parent->getPosition() + velocity;

        movePosition.x = std::clamp(movePosition.x, boundingBox.left, boundingBox.width);
        movePosition.y = std::clamp(movePosition.y, boundingBox.top, boundingBox.height);

        velocity = movePosition - parent->getPosition();
    }
}
