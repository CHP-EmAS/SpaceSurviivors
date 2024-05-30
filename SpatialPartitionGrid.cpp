#include <string> 

#include "SpatialPartitionGrid.h"
#include "Locator.h"

SpatialPartitionGrid::SpatialPartitionGrid()
{
	debugBox.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	debugBox.setOutlineColor(sf::Color::Blue);
	debugBox.setOutlineThickness(1);
	debugBox.setFillColor(sf::Color::Transparent);

	debugText.setFont(Locator::getGraphicService().getFont(GraphicService::Arial));
	debugText.setCharacterSize(20);
	debugText.setFillColor(sf::Color::White);

	for (int x = 0; x < PARTITION_SIZE; x++) {
		for (int y = 0; y < PARTITION_SIZE; y++) {
			cells[x][y] = nullptr;
		}
	}
}

void SpatialPartitionGrid::add(GameObject* object, bool isNewObject)
{
	sf::Vector2i cell = convertPositionToCell(object->getPosition());

	//out of bounds spawn
	if (cell.x < 0 || cell.x >= PARTITION_SIZE || cell.y < 0 || cell.y >= PARTITION_SIZE) {
		notifyObservers(Event::GRID_OBJECT_OUT_OF_BOUNDS, { object });
		cemetery.push_back(object);
		return;
	}

	object->prevObject = nullptr;
	object->nextObject = cells[cell.x][cell.y];
	cells[cell.x][cell.y] = object;

	if(object->nextObject != nullptr) {
		object->nextObject->prevObject = object;
	}

	if (isNewObject) {
		notifyObservers(Event::GRID_OBJECT_SPAWNED, { object });
	}
}

void SpatialPartitionGrid::remove(GameObject* object)
{
	sf::Vector2i currentCell = convertPositionToCell(object->getPosition());

	if (object->prevObject != nullptr) {
		object->prevObject->nextObject = object->nextObject;
	}

	if (object->nextObject != nullptr) {
		object->nextObject->prevObject = object->prevObject;
	}

	if (cells[currentCell.x][currentCell.y] == object) {
		cells[currentCell.x][currentCell.y] = object->nextObject;
	}

	cemetery.push_back(object);
}

std::vector<GameObject*> SpatialPartitionGrid::getCollidingObjects(GameObject* collider)
{
	std::vector<GameObject*> collidingObjects;

	sf::Vector2i cellToCheck = convertPositionToCell(collider->getPosition());
	for (int nx = -1; nx < 2; nx++) {
		for (int ny = -1; ny < 2; ny++) {
			sf::Vector2i adjacentCell = cellToCheck + sf::Vector2i(nx, ny);
		
			if (adjacentCell.x < 0 || adjacentCell.x >= PARTITION_SIZE || adjacentCell.y < 0 || adjacentCell.y >= PARTITION_SIZE) {
				continue;
			}

			GameObject* object = cells[adjacentCell.x][adjacentCell.y];
			while (object != nullptr) {
				if (collider == object) {
					object = object->nextObject;
					continue;
				}

				if (object->collider.isCollidingWith(&collider->collider)) {
					collidingObjects.push_back(object);
				}

				object = object->nextObject;
			}
		}
	}

	return collidingObjects;
}

void SpatialPartitionGrid::onObjectPositionUpdated(GameObject* object, sf::Vector2f lastPostion)
{
	sf::Vector2i newCell = convertPositionToCell(object->getPosition());
	sf::Vector2i oldCell = convertPositionToCell(lastPostion);

	if (newCell == oldCell) {
		return;
	}

	if (object->prevObject != nullptr) {
		object->prevObject->nextObject = object->nextObject;
	}

	if (object->nextObject != nullptr) {
		object->nextObject->prevObject = object->prevObject;
	}

	if (cells[oldCell.x][oldCell.y] == object) {
		cells[oldCell.x][oldCell.y] = object->nextObject;
	}

	object->prevObject = nullptr;
	object->nextObject = nullptr;

	add(object, false);
}

void SpatialPartitionGrid::updateAll(sf::Time deltaTime, GameState& state)
{
	for (int x = 0; x < PARTITION_SIZE; x++) {
		for (int y = 0; y < PARTITION_SIZE; y++) {
			GameObject* object = cells[x][y];
			while (object != nullptr) {
				object->update(deltaTime, state);

				if (object->markedForDespawn) {
					GameObject* toDelete = object;
					object = object->nextObject;
					remove(toDelete);
				} else {
					object = object->nextObject;
				}
			}
		}
	}

	//delete all objects that are not part of the grid anymore
	//deleting player object is handled by GameScene
	while (cemetery.size() > 0) {
		GameObject* obj = cemetery.back();
		if (obj->type != GameObject::O_Player) {
			notifyObservers(Event::GRID_OBJECT_DESPAWNED, { obj });
			delete obj;
		}
		cemetery.pop_back();
	}
}

void SpatialPartitionGrid::drawAll(sf::RenderWindow& window)
{
	for (int x = 0; x < PARTITION_SIZE; x++) {
		for (int y = 0; y < PARTITION_SIZE; y++) {
			GameObject* object = cells[x][y];
			while (object != nullptr) {
				window.draw(*object);
				object = object->nextObject;
			}
		}
	}
}

void SpatialPartitionGrid::debugDraw(sf::RenderWindow& window)
{
	for (int x = 0; x < PARTITION_SIZE; x++) {
		for (int y = 0; y < PARTITION_SIZE; y++) {
			debugBox.setPosition((x * CELL_SIZE) - CELL_SIZE, (y * CELL_SIZE) - CELL_SIZE);
			window.draw(debugBox);
	
			int length = 0;
			GameObject* beginn = cells[x][y];
	
			while (beginn != nullptr) {
				length++;
				beginn = beginn->nextObject;
			}
	
			debugText.setPosition((x * CELL_SIZE) - CELL_SIZE + 4, (y * CELL_SIZE) - CELL_SIZE);
			debugText.setString(std::to_string(length));
			window.draw(debugText);
		}
	}
}

sf::Vector2i SpatialPartitionGrid::convertPositionToCell(sf::Vector2f position)
{
	int cellX = (int)floorf((position.x + CELL_SIZE) / CELL_SIZE);
	int cellY = (int)floorf((position.y + CELL_SIZE) / CELL_SIZE);

	return sf::Vector2i(cellX, cellY);
}
