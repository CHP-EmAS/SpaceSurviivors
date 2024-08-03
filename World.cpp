#include "World.h"

#include "Locator.h"
#include "Scene.h"
#include "GameOver.h"
#include "GameObjectFactory.h"

World::World()
{
	validArea = sf::FloatRect(-100, -100, 1200, 1200);
}

void World::initialize()
{
	player.reset(new Player());
	player->initializeComponents();
	
	spawnObject(player, sf::Vector2f(WORLD_SIZE / 2, WORLD_SIZE / 2));

	spawnExperiencePuddle(sf::IntRect(10, 10, 980, 980), 10);
}

void World::reset()
{
	player.reset();
	objects.clear();
}

std::vector<std::shared_ptr<GameObject>> World::getAllObjects()
{
	return objects;
}

void World::spawnObject(std::shared_ptr<GameObject> object, sf::Vector2f spawnPoint)
{
	newlySpawnedObjects.push_back(object);
	object->spaw(spawnPoint);
	EventDispatcher::dispatch(Event(EventType::OBJECT_SPAWNED, object));
}

void World::update(const sf::Time& deltaTime)
{
	updateObjects(deltaTime);
	enemySpawner.checkSpawnConditions(deltaTime, *player);
	background.update(player->getPosition());
}

void World::spawnExperiencePuddle(sf::IntRect area, int totalAmount)
{
	for (int i = 0; i < totalAmount; i++) {
		int x = rand() % area.width;
		int y = rand() % area.height;

		x += area.left;
		y += area.top;

		auto experiece = Locator::get<GameObjectFactory>()->acquireExperience(1);
		spawnObject(experiece, sf::Vector2f(x, y));
	}
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);

	for (auto& obj : objects) {
		obj->draw(target, states);
	}
}

void World::updateObjects(const sf::Time& deltaTime)
{
	auto it = objects.begin();

	while (it != objects.end())
	{
		auto& obj = *it;

		//update
		obj->update(deltaTime);
		
		//object requests despawn
		if (!obj->isEnabled()) {
			EventDispatcher::dispatch(Event(EventType::OBJECT_DESPAWNED, obj));
			it = objects.erase(it);
			continue;
		}

		//out of bounds despawn
		if (!validArea.contains(obj->getPosition())) {
			EventDispatcher::dispatch(Event(EventType::OBJECT_DESPAWNED, obj));
			it = objects.erase(it);
			continue;
		}

		++it;
	}

	if (newlySpawnedObjects.size() > 0) {
		objects.insert(objects.end(), newlySpawnedObjects.begin(), newlySpawnedObjects.end());
		newlySpawnedObjects.clear();
	}
}
