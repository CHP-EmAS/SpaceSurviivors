#include "GridComponent.h"
#include "CollisionGrid.h"

#include "BoxCollider.h"
#include "CircleCollider.h"

#include "Locator.h"

GridComponent::GridComponent(std::shared_ptr<GameObject> parent, GRID spawnGrid) 
	: Component(parent), spawnGrid(spawnGrid), managedByGrid(false) {}

const sf::FloatRect GridComponent::getBoundingBox() const
{
	if (auto parent = _parent.lock()) {
		if (parent->hasComponent<BoxCollider>())
		{
			return parent->getComponent<BoxCollider>()->getContainingAABB();
		}

		if (parent->hasComponent<CircleCollider>())
		{
			return parent->getComponent<CircleCollider>()->getContainingAABB();
		}

		return sf::FloatRect(parent->getPosition(), sf::Vector2f(0,0));
	}

	return sf::FloatRect();
}

GRID GridComponent::isOnGrid() const
{
	if (managedByGrid)
		return spawnGrid;

	return GRID::G_NONE;
}

void GridComponent::addSelfToCollisionGrid()
{
	if (_parent.expired()) {
		return;
	}

	if (managedByGrid) {
		onDespawn();
	}

	std::shared_ptr<GameObject> parent = _parent.lock();

	if (Locator::get<CollisionGrid>()->add(parent, spawnGrid, getBoundingBox(), cellPositions[0], cellPositions[1])) {
		managedByGrid = true;
	}
}

void GridComponent::removeSelfFromCollisionGrid()
{
	if (!managedByGrid || _parent.expired()) {
		return;
	}

	std::shared_ptr<GameObject> parent = _parent.lock();

	Locator::get<CollisionGrid>()->remove(parent, spawnGrid, cellPositions[0], cellPositions[1]);

	managedByGrid = false;
}

void GridComponent::onSpawn()
{
	addSelfToCollisionGrid();
}

void GridComponent::onDespawn()
{
	removeSelfFromCollisionGrid();
}

void GridComponent::onPostUpdate()
{
	if (spawnGrid == G_STATIC || !managedByGrid || _parent.expired()) {
		return;
	}

	std::shared_ptr<GameObject> parent = _parent.lock();

	if (!Locator::get<CollisionGrid>()->move(parent, spawnGrid, getBoundingBox(), cellPositions[0], cellPositions[1])) {
		parent->despawn();
		managedByGrid = false;
	}
}
