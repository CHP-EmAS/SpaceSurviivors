#pragma once

#include <typeindex>
#include "SFML/Graphics.hpp"

class GameObject;

class Component {
public:

	Component(std::shared_ptr<GameObject> parent) : parent_(parent) {}
	virtual ~Component() = default;

protected:
	std::weak_ptr<GameObject> parent_;
};