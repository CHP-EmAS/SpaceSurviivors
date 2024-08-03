#pragma once

#include <memory.h>
#include <SFML/Graphics.hpp>

#include "ObjectPool.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Explosion.h"

#include "CollisionGrid.h"

#include "ParallaxBackground.h"
#include "EnemySpawnController.h"
#include "GameObjectFactory.h"

#include "Player.h"


class World : public sf::Drawable
{
public:
	World();

	void initialize();
	void reset();

	std::vector<std::shared_ptr<GameObject>> getAllObjects();

	void spawnObject(std::shared_ptr<GameObject> object, sf::Vector2f spawnPoint);
	void update(const sf::Time& deltaTime);

	void spawnExperiencePuddle(sf::IntRect area, int totalAmount);
private:
	ParallaxBackground background;
	std::shared_ptr<Player> player;
	
	sf::FloatRect validArea;

	EnemySpawnController enemySpawner;

	std::vector<std::shared_ptr<GameObject>> objects;
	std::vector<std::shared_ptr<GameObject>> newlySpawnedObjects;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateObjects(const sf::Time& deltaTime);
};
