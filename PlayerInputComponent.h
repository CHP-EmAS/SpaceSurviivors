#pragma once

#include <SFML/Graphics.hpp>

#include "Component.h"

class PlayerInputComponent : public Component {
public:
	PlayerInputComponent(std::shared_ptr<GameObject> parent);
	~PlayerInputComponent();

	void checkInput(sf::Time deltaTime);

private:
	void rotateToMouse(sf::Time deltaTime);

};