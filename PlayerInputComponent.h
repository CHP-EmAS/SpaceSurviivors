#pragma once

#include <SFML/Graphics.hpp>

#include "Component.h"

class PlayerInputComponent : public Component {
public:
	PlayerInputComponent(std::shared_ptr<GameObject> parent);
	~PlayerInputComponent();

	void onUpdate(const sf::Time& deltaTime) override;

private:
	void rotateToMouse(const sf::Time& deltaTime);

};