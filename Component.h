#pragma once

#include "Event.h"
#include "SFML/Graphics.hpp"

class GameObject;

class Component {
public:

	Component(std::shared_ptr<GameObject>& parent) : _parent(parent) {}
	virtual ~Component() = default;

	virtual void onSpawn() {};
	
	virtual void onEvent(const Event& event) {};

	virtual void onUpdate(const sf::Time& deltaTime) {};
	virtual void onSimulate(const sf::Time& deltaTime) {};
	virtual void onPostUpdate() {};

	virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const {};
	virtual void onDebugDraw(sf::RenderTarget& target, sf::RenderStates states) const {};

	virtual void onDespawn() {};
	
protected:
	std::weak_ptr<GameObject> _parent;
};