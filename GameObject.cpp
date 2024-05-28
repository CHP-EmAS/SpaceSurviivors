#include "GameObject.h"
#include "Locator.h"
#include "VectorExtension.h"
#include "SpatialPartitionGrid.h"

GameObject::GameObject(ObjectType type) : controller(nullptr), type(type)
{
	setPosition(sf::Vector2f(0,0));
	markedForDespawn = false;

	controller = nullptr;

	grid = nullptr;
	nextObject = nullptr;
	prevObject = nullptr;
}


void GameObject::update(sf::Time deltaTime)
{
	sf::Vector2f lastPosition = getPosition();

	if (controller) {
		controller->simulate(deltaTime);
	}

	if (grid) {
		grid->onObjectPositionUpdated(this, lastPosition);
	}
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);

	if (Locator::getSceneManager().debugDrawEnabled()) {
		target.draw(collider, states);
	}
}

void GameObject::interact(Interaction action, GameObject& interactor)
{
	std::cout << "Actor " << &interactor << " interacted with Action <" << action << ">" << std::endl;
}

void GameObject::spawOnGrid(SpatialPartitionGrid* grid, sf::Vector2f position)
{
	markedForDespawn = false;
	setPosition(position);
	this->grid = grid;

	grid->add(this);
}

void GameObject::markForDespawn()
{
	markedForDespawn = true;
}

void GameObject::setController(Controller* newController)
{
	if (controller)
	{
		delete controller;
	}
	controller = newController;
}

Controller* GameObject::getController()
{
	return controller;
}

Collider* GameObject::getCollider()
{
	return &collider;
}

GameObject::ObjectType GameObject::getType() const
{
	return this->type;
}

GameObject::~GameObject()
{
	delete controller;
}
