#pragma once

#include "Defines.h"
#include "Observable.h"
#include "GameObject.h"

class SpatialPartitionGrid : public Observable
{
public:
	static const int PARTITION_SIZE = 12;
	static const int CELL_SIZE = WINDOW_SIZE / (PARTITION_SIZE - 2);

	SpatialPartitionGrid();

	void add(GameObject* object, bool isNewObject = true);
	void remove(GameObject* object);

	std::vector<GameObject*> getCollidingObjects(GameObject* collider);

	void onObjectPositionUpdated(GameObject* enemy, sf::Vector2f lastPostion);

	void updateAll(sf::Time deltaTime, GameState& state);
	void drawAll(sf::RenderWindow& window);

	void debugDraw(sf::RenderWindow& window);

private:
	GameObject* cells[PARTITION_SIZE][PARTITION_SIZE];
	std::vector<GameObject*> cemetery;

	sf::Vector2i convertPositionToCell(sf::Vector2f position);

	sf::RectangleShape debugBox;
	sf::Text debugText;
};

