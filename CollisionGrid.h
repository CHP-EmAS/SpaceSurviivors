#pragma once

#include <list>
#include <unordered_set>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Defines.h"
#include "GameObject.h"
#include "Experience.h"

enum GRID {
	G_DYNAMIC,
	G_STATIC,
	G_ALL,
	G_NONE
};

class CollisionGrid
{
public:
	static const int PARTITION_SIZE = 12;
	static const int CELL_SIZE = WORLD_SIZE / (PARTITION_SIZE - 2);

	CollisionGrid();
	~CollisionGrid();

	void clear();

	bool add(std::shared_ptr<GameObject>& object, GRID grid, sf::FloatRect aabb, sf::Vector2i& refTopLeft, sf::Vector2i& refBottomRight);
	bool move(std::shared_ptr<GameObject>& object, GRID grid, sf::FloatRect aabb, sf::Vector2i& lastTopLeft, sf::Vector2i& lastBottomRight);
	int remove(std::shared_ptr<GameObject>& object, GRID grid, sf::Vector2i& topLeft, sf::Vector2i& bottomRight);

	std::unordered_set<std::shared_ptr<GameObject>> getCollidingObjects(std::shared_ptr<GameObject>& object, GRID grid);
	std::unordered_set<std::shared_ptr<GameObject>> getCollidingObjects(Collider& collider, GRID grid, GameObject* boundObject = nullptr);
	std::unordered_set<std::shared_ptr<GameObject>> getCollidingObjectsLazy(sf::FloatRect area, GRID grid);

	void debugDraw(sf::RenderTarget& window);

private:

	sf::RectangleShape debugBox;
	sf::Text debugText;

	std::list<std::shared_ptr<GameObject>> dynamicCells[PARTITION_SIZE][PARTITION_SIZE];
	std::list<std::shared_ptr<GameObject>> staticCells[PARTITION_SIZE][PARTITION_SIZE];

	std::unordered_set<std::shared_ptr<GameObject>> getObjectsInArea(const sf::Vector2i& topLeft, const sf::Vector2i& bottomRight, GRID grid) const;

	const sf::Vector2i convertPositionToCell(const sf::Vector2f position) const;
	const std::array<sf::Vector2i, 2> mapAreaToCellArea(sf::FloatRect area) const;
};

