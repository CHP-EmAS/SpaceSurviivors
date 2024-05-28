#pragma once
#include "Controller.h"
class AsteroidController : public Controller
{
public:
    AsteroidController(GameObject* parent, sf::Vector2f direction, float speed, float rotationSpeed);
    void simulate(sf::Time deltaTime) override;

private:
    float rotationSpeed;

};

