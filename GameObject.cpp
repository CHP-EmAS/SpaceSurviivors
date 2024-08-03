#include "GameObject.h"

#include <iostream>
#include "Locator.h"

GameObject::GameObject(ObjectType type) : type(type)
{
	setPosition(sf::Vector2f(0,0));
}

void GameObject::update(const sf::Time& deltaTime)
{
	for (const auto& componentPair : components) {
		componentPair.second->onUpdate(deltaTime);
		componentPair.second->onSimulate(deltaTime);
		componentPair.second->onPostUpdate();
	}
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (const auto& componentPair : components) {
		componentPair.second->onDraw(target, states);
		componentPair.second->onDebugDraw(target, states);
	}
}

void GameObject::interact(const Event& event)
{
	for (const auto& componentPair : components) {
		componentPair.second->onEvent(event);
	}
}

void GameObject::spaw(sf::Vector2f spawnPosition)
{
	setPosition(spawnPosition);

	for (const auto& componentPair : components) {
		componentPair.second->onSpawn();
	}

	enabled = true;
}

void GameObject::despawn()
{
	for (const auto& componentPair : components) {
		componentPair.second->onDespawn();
	}

	enabled = false;
}

bool GameObject::isEnabled() const
{
	return enabled;
}
