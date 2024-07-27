#include <string> 

#include "VectorExtension.h"

#include "PartitionedLayer.h"
#include "Locator.h"

#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

#include "Event.h"
#include "GameObject.h"

PartitionedLayer::PartitionedLayer()
{
	debugBox.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	debugBox.setOutlineColor(sf::Color::Blue);
	debugBox.setOutlineThickness(1);
	debugBox.setFillColor(sf::Color::Transparent);

	debugText.setFont(Locator::getGraphicService().getFont(GraphicService::Arial));
	debugText.setCharacterSize(20);
	debugText.setFillColor(sf::Color::White);
}

void PartitionedLayer::add(std::shared_ptr<GameObject> object, bool isNewObject)
{
	sf::Vector2i cell = convertPositionToCell(object->getPosition());

	//out of bounds spawn
	if (cell.x < 0 || cell.x >= PARTITION_SIZE || cell.y < 0 || cell.y >= PARTITION_SIZE) {
		object->despawn();
		broadcastEvent(Event::Event(Event::GRID_OBJECT_OUT_OF_BOUNDS, object));
		return;
	}

	if (object->type != O_Experience) {
		cells[cell.x][cell.y].push_back(object);
	} else {
		experience[cell.x][cell.y].push_back(std::dynamic_pointer_cast<Experience>(object));
	}
	
	if (isNewObject) {
		broadcastEvent(Event::Event(Event::GRID_OBJECT_SPAWNED, object));
	}
}

void PartitionedLayer::clear()
{
	for (int x = 0; x < PARTITION_SIZE; x++) {
		for (int y = 0; y < PARTITION_SIZE; y++) {

			for (auto& obj : cells[x][y]) {
				obj->despawn();
				broadcastEvent(Event::Event(Event::GRID_OBJECT_DESPAWNED, obj));
			}

			cells[x][y].clear();
		}
	}
}

std::vector<std::shared_ptr<GameObject>> PartitionedLayer::getCollidingObjects(std::shared_ptr<GameObject> object)
{
	std::vector<std::shared_ptr<GameObject>> collidingObjects;

	Collider* firstCollider = nullptr;
	if (object->hasComponent<BoxCollider>()) {
		firstCollider = object->getComponent<BoxCollider>();
	} else if (object->hasComponent<CircleCollider>()) {
		firstCollider = object->getComponent<CircleCollider>();
	}

	if (firstCollider == nullptr) {
		return collidingObjects;
	}

	sf::Vector2i cellToCheck = convertPositionToCell(object->getPosition());

	for (int nx = -1; nx < 2; nx++) {
		for (int ny = -1; ny < 2; ny++) {
			sf::Vector2i adjacentCell = cellToCheck + sf::Vector2i(nx, ny);
		
			if (adjacentCell.x < 0 || adjacentCell.x >= PARTITION_SIZE || adjacentCell.y < 0 || adjacentCell.y >= PARTITION_SIZE) {
				continue;
			}

			for (auto& otherObject : cells[adjacentCell.x][adjacentCell.y]) {
				if (object == otherObject) {
					continue;
				}

				Collider* secondCollider = nullptr;
				if (otherObject->hasComponent<BoxCollider>()) {
					secondCollider = otherObject->getComponent<BoxCollider>();
				}
				else if (otherObject->hasComponent<CircleCollider>()) {
					secondCollider = otherObject->getComponent<CircleCollider>();
				}

				if (secondCollider) {
					if (firstCollider->isCollidingWith(*secondCollider)) {
						collidingObjects.push_back(otherObject);
					}
				} else { // use position point if no second collider
					if (firstCollider->isCollidingWith(otherObject->getPosition())) {
						collidingObjects.push_back(otherObject);
					}
				}

				
			}
		}
	}

	return collidingObjects;
}

std::vector<std::shared_ptr<Experience>> PartitionedLayer::collectExperiences(std::weak_ptr<GameObject> target, float triggerRadius)
{
	std::vector<std::shared_ptr<Experience>> collectedExperience;

	sf::Vector2f targetPosition = target.lock()->getPosition();
	sf::Vector2f vTriggerRadius(triggerRadius, triggerRadius);

	sf::Vector2i topLeftCell = convertPositionToCell(targetPosition - vTriggerRadius);
	sf::Vector2i bottomRightCell = convertPositionToCell(targetPosition + vTriggerRadius);

	for (int x = topLeftCell.x; x <= bottomRightCell.x; x++) {
		for (int y = topLeftCell.y; y <= bottomRightCell.y; y++) {
			sf::Vector2i expCell = sf::Vector2i(x, y);

			if (expCell.x < 0 || expCell.x >= PARTITION_SIZE || expCell.y < 0 || expCell.y >= PARTITION_SIZE) {
				continue;
			}

			for (auto& exp : experience[x][y])
			{
				sf::Vector2f diff = exp->getPosition() - targetPosition;

				float squareDistance = vectorSquareLength(diff);

				//if triggerd check if collectable
				if (!exp->isTriggerd()) {
					float squareRadius = triggerRadius * triggerRadius;

					if (squareDistance <= squareRadius) {
						exp->trigger(target);
					}
				}

			}
		}
	}

	return collectedExperience;
}

std::list<std::shared_ptr<GameObject>> PartitionedLayer::getAllObjects()
{
	std::list<std::shared_ptr<GameObject>> objects;

	for (int x = 0; x < PARTITION_SIZE; x++) {
		for (int y = 0; y < PARTITION_SIZE; y++) {
			for (auto& obj : cells[x][y]) {
				objects.push_back(obj);
			}
		}
	}

	return objects;
}

void PartitionedLayer::updateGridObjects(sf::Time deltaTime, GameState& state)
{
	for (int x = 0; x < PARTITION_SIZE; x++) {
		for (int y = 0; y < PARTITION_SIZE; y++) {
			//Use Iterator because we manipulate the list while iterating over it
			auto it = cells[x][y].begin();

			while (it != cells[x][y].end())
			{
				std::shared_ptr<GameObject> obj = *it;

				//Update
				sf::Vector2i oldCell = sf::Vector2i(x, y);
				obj->update(deltaTime, state);
				sf::Vector2i newCell = convertPositionToCell(obj->getPosition());

				//Object requests despawn
				if (!obj->isEnabled()) {
					broadcastEvent(Event::Event(Event::GRID_OBJECT_DESPAWNED, obj));
					it = cells[x][y].erase(it);
					continue;
				}

				//Object moved to other cell
				if (newCell == oldCell) {
					++it;
					continue;
				}

				add(obj, false);
				it = cells[x][y].erase(it);
			}

			//Experience
			for (auto& obj : experience[x][y]) {
				obj->update(deltaTime, state);
			}
		}
	}
}

void PartitionedLayer::debugDraw(sf::RenderTarget& window)
{
	if (Locator::getSceneManager().debugShowSpatialGrid()) {
		for (int x = 0; x < PARTITION_SIZE; x++) {
			for (int y = 0; y < PARTITION_SIZE; y++) {
				debugBox.setPosition((x * CELL_SIZE) - (CELL_SIZE * 2), (y * CELL_SIZE) - (CELL_SIZE * 2));
				window.draw(debugBox);

				int length = cells[x][y].size();

				debugText.setPosition((x * CELL_SIZE) - (CELL_SIZE * 2) + 4, (y * CELL_SIZE) - (CELL_SIZE * 2));
				debugText.setString(std::to_string(length));
				window.draw(debugText);
			}
		}
	}
}

const sf::Vector2i PartitionedLayer::convertPositionToCell(const sf::Vector2f position) const
{
	int cellX = static_cast<int>(std::floor((position.x + (CELL_SIZE * 2)) / CELL_SIZE));
	int cellY = static_cast<int>(std::floor((position.y + (CELL_SIZE * 2)) / CELL_SIZE));

	return sf::Vector2i(cellX, cellY);
}

void PartitionedLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int x = 0; x < PARTITION_SIZE; x++) {
		for (int y = 0; y < PARTITION_SIZE; y++) {
			for (auto& obj : experience[x][y]) {
				target.draw(*obj, states);
			}
		}
	}

	for (int x = 0; x < PARTITION_SIZE; x++) {
		for (int y = 0; y < PARTITION_SIZE; y++) {
			for (auto& obj : cells[x][y]) {
				target.draw(*obj, states);
			}
		}
	}
}

PartitionedLayer::~PartitionedLayer()
{

}
