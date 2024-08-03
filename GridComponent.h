#pragma once
#include <array>

#include "Component.h"

enum GRID;

class GridComponent : public Component
{
public:
	GridComponent(std::shared_ptr<GameObject> parent, GRID spawnGrid);
	~GridComponent() = default;

	const sf::FloatRect getBoundingBox() const;
	GRID isOnGrid() const;

	void addSelfToCollisionGrid();
	void removeSelfFromCollisionGrid();
	
private:
	const GRID spawnGrid;
	bool managedByGrid;

	std::array<sf::Vector2i, 2> cellPositions;

	void onSpawn() override;
	void onDespawn() override;
	void onPostUpdate() override;
};

