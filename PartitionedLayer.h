#pragma once

#include <list>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Defines.h"
#include "Observable.h"
#include "GameObject.h"
#include "Experience.h"

class PartitionedLayer : public sf::Drawable, public Observable
{
public:
	static const int PARTITION_SIZE = 14;
	static const int CELL_SIZE = WORLD_SIZE / (PARTITION_SIZE - 4);

	PartitionedLayer();

	void add(std::shared_ptr<GameObject> object, bool isNewObject = true);
	void clear();
	
	std::vector<std::shared_ptr<GameObject>> getCollidingObjects(std::shared_ptr<GameObject> object);
	std::vector<std::shared_ptr<Experience>> collectExperiences(std::weak_ptr<GameObject> target, float triggerRadius);

	std::list<std::shared_ptr<GameObject>> getAllObjects();

	void updateGridObjects(sf::Time deltaTime, GameState& state);

	void debugDraw(sf::RenderTarget& window);

	~PartitionedLayer();
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const sf::Vector2i convertPositionToCell(const sf::Vector2f position) const;

	sf::RectangleShape debugBox;
	sf::Text debugText;

	std::list<std::shared_ptr<GameObject>> cells[PARTITION_SIZE][PARTITION_SIZE];

	std::list<std::shared_ptr<Experience>> experience[PARTITION_SIZE][PARTITION_SIZE];
};

