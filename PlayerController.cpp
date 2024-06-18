#include <SFML/Window/Keyboard.hpp>
#include <iostream>

#include "Defines.h"
#include "Locator.h"

#include "PlayerController.h"
#include "GameObject.h"
#include "VectorExtension.h"

PlayerController::PlayerController(GameObject* parent) : Controller(parent) {
	velocity = sf::Vector2f(0, 0);
	maxSpeed = 1800.f;
	friction = 0.01;
}

void PlayerController::simulate(sf::Time deltaTime, GameState& state)
{
    sf::Vector2f lastVelocity(velocity);

    velocity += getInputVector() * state.getPlayerAcceleration() * deltaTime.asSeconds();;

    if (velocity != sf::Vector2f(0, 0)) {
        if (std::sqrt(VectorExtension::vectorSquareLength(velocity)) > maxSpeed)
        {
            float angle = std::atan2(velocity.y, velocity.x);
            velocity.x = maxSpeed * std::cos(angle);
            velocity.y = maxSpeed * std::sin(angle);
        }
        
        velocity *= std::powf(friction, deltaTime.asSeconds());

        
        if (std::abs(velocity.x) < std::abs(lastVelocity.x) && std::abs(velocity.x) < 5.f) velocity.x = 0.f;
        if (std::abs(velocity.y) < std::abs(lastVelocity.y) && std::abs(velocity.y) < 5.f) velocity.y = 0.f;

        clipToBoundingBox();
        parentObject->move(velocity * deltaTime.asSeconds());
    }
       
    rotateToMouse(deltaTime, state);
}

sf::Vector2f PlayerController::getInputVector()
{
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        movement.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        movement.y += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        movement.x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        movement.x += 1;
    }

    if (movement == sf::Vector2f(0, 0)) {
        return sf::Vector2f(0, 0);
    }
    
    return VectorExtension::normalize(movement);
}

void PlayerController::rotateToMouse(sf::Time deltaTime, GameState& state)
{
    sf::Vector2f mousePosition = Locator::getSceneManager().getMousePosition();

    float targetAngle = VectorExtension::getAngle(mousePosition - parentObject->getPosition());
    float deltaAngle = targetAngle - parentObject->getRotation();

    if (deltaAngle > 180.f) deltaAngle -= 360.f;
    if (deltaAngle < -180.f) deltaAngle += 360.f;

    float maxRotation = 240 * (state.getPlayerAcceleration() / 1500.f) * deltaTime.asSeconds();

    if (std::abs(deltaAngle) < maxRotation) {
        parentObject->setRotation(targetAngle);
    } else {
        if (deltaAngle > 0) {
            parentObject->rotate(maxRotation);
        } else {
            parentObject->rotate(-maxRotation);
        }
    }
}

void PlayerController::clipToBoundingBox()
{
    sf::Vector2f movePosition = parentObject->getPosition() + velocity;

    movePosition.x = std::clamp(movePosition.x, 10.f, static_cast<float>(WINDOW_SIZE) - 10);
    movePosition.y = std::clamp(movePosition.y, 10.f, static_cast<float>(WINDOW_SIZE) - 10);

    velocity = movePosition - parentObject->getPosition();
}
