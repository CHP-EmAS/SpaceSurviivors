#include "GameObject.h"

#include <iostream>
#include "Locator.h"

GameObject::GameObject(ObjectType type) : type(type)
{
	enabled = false;

	setPosition(sf::Vector2f(0,0));
}

void GameObject::interact(const Event event)
{
	std::cout << "Actor interacted with Action <" << event.type << "> to Base" << std::endl;
}

void GameObject::spaw(sf::Vector2f spawnPosition, ObjectLayer layer)
{
	if (enabled) {
		return;
	}

	setPosition(spawnPosition);

	switch (layer) {
	case L_Collision:
		Locator::getGameWorld().getCollisionLayer().add(shared_from_this());
		break;
	case L_Effect:
		Locator::getGameWorld().getEffectLayer().add(shared_from_this());
		break;
	}
	
	
	enabled = true;
}

void GameObject::despawn()
{
	enabled = false;
}

bool GameObject::isEnabled() const
{
	return enabled;
}
