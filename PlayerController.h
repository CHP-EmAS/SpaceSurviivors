#pragma once
#include "Controller.h"
class PlayerController : public Controller
{
public:
    PlayerController(GameObject* parent);

	void simulate(sf::Time deltaTime, GameState& state) override;
private:
    sf::Vector2f getInputVector();
    
    void rotateToMouse(sf::Time elapsedTime);
    void clipToBoundingBox();
};

