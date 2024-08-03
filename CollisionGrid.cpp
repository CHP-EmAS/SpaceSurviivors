#include <string> 

#include "VectorExtension.h"

#include "CollisionGrid.h"
#include "Locator.h"

#include "GridComponent.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

#include "Event.h"
#include "GameObject.h"

CollisionGrid::CollisionGrid()
{
	debugBox.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	debugBox.setOutlineColor(sf::Color::Blue);
	debugBox.setOutlineThickness(1);
	debugBox.setFillColor(sf::Color::Transparent);

	debugText.setFont(Locator::get<GraphicService>()->getFont(GraphicService::Arial));
	debugText.setCharacterSize(20);
	debugText.setFillColor(sf::Color::Yellow);
}

CollisionGrid::~CollisionGrid()
{

}

void CollisionGrid::clear()
{
	for (int x = 0; x < PARTITION_SIZE; x++) {
		for (int y = 0; y < PARTITION_SIZE; y++) {
			dynamicCells[x]->clear();
			staticCells[x]->clear();
		}
	}
}

std::unordered_set<std::shared_ptr<GameObject>> CollisionGrid::getCollidingObjects(std::shared_ptr<GameObject>& object, GRID grid)
{
	std::unordered_set<std::shared_ptr<GameObject>> collidingObjects;

	Collider* firstCollider = firstCollider = object->getComponent<CircleCollider>();
	if (!firstCollider) {
		firstCollider = object->getComponent<BoxCollider>();
	}

	if (!firstCollider) {
		std::cout << "CANNOT GET COLLIDING OBJECTS! REQUESTING GAME OBJECT HAS NO COLLIDER..." << std::endl;
		return collidingObjects;
	}

	return getCollidingObjects(*firstCollider, grid, object.get());
}

std::unordered_set<std::shared_ptr<GameObject>> CollisionGrid::getCollidingObjects(Collider& collider, GRID grid, GameObject* boundObject)
{
	std::array<sf::Vector2i, 2> corner = mapAreaToCellArea(collider.getContainingAABB());
	std::unordered_set<std::shared_ptr<GameObject>> collidingObjects = getObjectsInArea(corner[0], corner[1], grid);

	auto it = collidingObjects.begin();
	while (it != collidingObjects.end())
	{
		std::shared_ptr<GameObject> other = *it;

		if (boundObject == other.get()) {
			it = collidingObjects.erase(it);
			continue;
		}

		Collider* secondCollider = other->getComponent<CircleCollider>();
		if (!secondCollider) {
			secondCollider = other->getComponent<BoxCollider>();
		}

		if (secondCollider) {
			if (!collider.isCollidingWith(*secondCollider)) {
				it = collidingObjects.erase(it);
				continue;
			}
		}
		else { // use position point if no second collider
			if (!collider.isCollidingWith(other->getPosition())) {
				it = collidingObjects.erase(it);
				continue;
			}
		}

		++it;
	}

	return collidingObjects;
}

std::unordered_set<std::shared_ptr<GameObject>> CollisionGrid::getCollidingObjectsLazy(sf::FloatRect area, GRID grid)
{
	std::array<sf::Vector2i, 2> corner = mapAreaToCellArea(area);
	return getObjectsInArea(corner[0], corner[1], grid);
}

void CollisionGrid::debugDraw(sf::RenderTarget& window)
{
	if (Locator::get<SceneManager>()->debugShowSpatialGrid()) {
		for (int x = 0; x < PARTITION_SIZE; x++) {
			for (int y = 0; y < PARTITION_SIZE; y++) {
				debugBox.setPosition((x * CELL_SIZE) - CELL_SIZE, (y * CELL_SIZE) - CELL_SIZE);
				window.draw(debugBox);

				int dynamicLength = dynamicCells[x][y].size();
				int staticLength = staticCells[x][y].size();

				debugText.setPosition((x * CELL_SIZE) - CELL_SIZE + 4, (y * CELL_SIZE) - CELL_SIZE);
				debugText.setString(std::to_string(dynamicLength) + ", " + std::to_string(staticLength));
				window.draw(debugText);
			}
		}
	}
}

bool CollisionGrid::add(std::shared_ptr<GameObject>& object, GRID grid, sf::FloatRect aabb, sf::Vector2i& refTopLeft, sf::Vector2i& refBottomRight)
{
	sf::Vector2i topLeft = convertPositionToCell(aabb.getPosition());
	sf::Vector2i bottomRight = convertPositionToCell(aabb.getPosition() + aabb.getSize());

	if (topLeft.x >= PARTITION_SIZE || topLeft.y > PARTITION_SIZE
		|| bottomRight.x < 0 || bottomRight.y < 0) {

		std::cout << "CANNOT ADD OBJECT TO COLLISION GIRD! COMPLETELY OUT OF BOUNDS..." << std::endl;
		return false;
	}

	refTopLeft = topLeft;
	refBottomRight = bottomRight;

	for (int x = topLeft.x; x <= bottomRight.x; x++) {
		for (int y = topLeft.y; y <= bottomRight.y; y++) {
			switch (grid) {
			case G_DYNAMIC:
				dynamicCells[x][y].push_back(object);
				break;
			case G_STATIC:
			default:
				staticCells[x][y].push_back(object);
				break;
			}
		}
	}

	return true;
}

bool CollisionGrid::move(std::shared_ptr<GameObject>& object, GRID grid, sf::FloatRect aabb, sf::Vector2i& lastTopLeft, sf::Vector2i& lastBottomRight)
{
	sf::Vector2i newTopLeft = convertPositionToCell(aabb.getPosition());
	sf::Vector2i newBottomRight = convertPositionToCell(aabb.getPosition() + aabb.getSize());
	
	if (newTopLeft == lastTopLeft && newBottomRight == lastBottomRight) {
		return true; //not moved to diffrent cells
	}

	remove(object, grid, lastTopLeft, lastBottomRight);
	return add(object, grid, aabb, lastTopLeft, lastBottomRight);
}

int CollisionGrid::remove(std::shared_ptr<GameObject>& object, GRID grid, sf::Vector2i& topLeft, sf::Vector2i& bottomRight)
{
	int removedObjects = 0;

	for (int x = topLeft.x; x <= bottomRight.x; x++) {
		for (int y = topLeft.y; y <= bottomRight.y; y++) {
			std::list<std::shared_ptr<GameObject>>* list;
			std::list<std::shared_ptr<GameObject>>::iterator beginn;
			std::list<std::shared_ptr<GameObject>>::iterator end;

			switch (grid) {
			case G_DYNAMIC:
				list = &dynamicCells[x][y];
				break;
			case G_STATIC:
				list = &staticCells[x][y];
				break;
			}

			beginn = list->begin();
			end = list->end();

			for (auto& it = beginn; it != end;) {
				auto& obj = *it;

				if (obj.get() == object.get()) {
					it = list->erase(it);
					removedObjects++;
					continue;
				}

				++it;
			}
		}
	}

	int expectedRemovedCount = (bottomRight.x - topLeft.x + 1) * (bottomRight.y - topLeft.y + 1);
	if (expectedRemovedCount != removedObjects) {
		std::cout << "REMOVED LESS OR MORE OBJECTS FROM COLLISION GIRD! SHOULD: " << expectedRemovedCount << " IS: " << removedObjects << std::endl;
	}

	return removedObjects;
}

std::unordered_set<std::shared_ptr<GameObject>> CollisionGrid::getObjectsInArea(const sf::Vector2i& topLeft, const sf::Vector2i& bottomRight, GRID grid) const
{
	std::unordered_set<std::shared_ptr<GameObject>> set;

	for (int x = topLeft.x; x <= bottomRight.x; x++) {
		for (int y = topLeft.y; y <= bottomRight.y; y++) {
			switch (grid) {
			case G_DYNAMIC:
			{
				auto& list = dynamicCells[x][y];
				set.insert(list.begin(), list.end());
				break;
			}
			case G_STATIC:
			default:
			{
				auto& list = staticCells[x][y];
				set.insert(list.begin(), list.end());
				break;
			}
			}
		}
	}

	return set;
}

const sf::Vector2i CollisionGrid::convertPositionToCell(const sf::Vector2f position) const
{
	int cellX = static_cast<int>(std::floor((position.x + CELL_SIZE) / CELL_SIZE));
	int cellY = static_cast<int>(std::floor((position.y + CELL_SIZE) / CELL_SIZE));

	cellX = std::clamp<int>(cellX, 0, PARTITION_SIZE - 1);
	cellY = std::clamp<int>(cellY, 0, PARTITION_SIZE - 1);

	return sf::Vector2i(cellX, cellY);
}

const std::array<sf::Vector2i, 2> CollisionGrid::mapAreaToCellArea(sf::FloatRect area) const
{
	std::array<sf::Vector2i, 2> cells;

	cells[0] = convertPositionToCell(area.getPosition());
	cells[1] = convertPositionToCell(area.getPosition() + area.getSize());

	return cells;
}
