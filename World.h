#pragma once

#include <memory.h>
#include <SFML/Graphics.hpp>

#include "ObjectPool.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Explosion.h"

#include "PartitionedLayer.h"
#include "EffectLayer.h"

#include "ParallaxBackground.h"
#include "EnemySpawnController.h"
#include "GameObjectFactory.h"

#include "Player.h"


class World : public sf::Drawable
{
public:
	void initialize(GameState& state);
	void reset(GameState& state);

	void update(const sf::Time deltaTime, GameState& state);

	PartitionedLayer& getCollisionLayer();
	EffectLayer& getEffectLayer();

	GameObjectFactory& getGameObjectFactory();
	EnemySpawnController& getEnemySpawnController();

	void spawnExperiencePuddle(sf::IntRect area, int totalAmount);
private:
	PartitionedLayer collisionLayer;
	EffectLayer effectLayer;

	GameObjectFactory objectFactory;
	EnemySpawnController enemySpawner;

	ParallaxBackground background;

	std::shared_ptr<Player> player;

	float gameOverTimer;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

