#include "AsteroidController.h"
#include "GameObject.h"
#include "VectorExtension.h"

AsteroidController::AsteroidController(GameObject* parent, sf::Vector2f direction, float speed, float rotationSpeed) : Controller(parent) {
	this->velocity = VectorExtension::normalize(direction) * speed;
	this->rotationSpeed = rotationSpeed;
}

void AsteroidController::simulate(sf::Time deltaTime, GameState& state)
{
	parentObject->move(velocity * deltaTime.asSeconds());
	parentObject->rotate(rotationSpeed * deltaTime.asSeconds());
}
