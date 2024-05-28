#pragma once
#include "Controller.h"
class PlayerController : public Controller
{
public:
    PlayerController(GameObject* parent);

	void simulate(sf::Time deltaTime) override;
private:
    sf::Vector2f getInputVelocity(sf::Time deltaTime);
    
    void rotateToMouse(sf::Time elapsedTime);
    void clipToBoundingBox();

    float acceleration;
};

