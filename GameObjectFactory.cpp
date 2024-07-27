#include "GameObjectFactory.h"

void GameObjectFactory::prepareObjects()
{
	fillPool(O_Asteroid, 10);
	fillPool(O_Bullet, 20);
	fillPool(O_Explosion, 5);
	fillPool(O_Experience, 30);
}

void GameObjectFactory::clear()
{
	asteroidPool.clear();
	bulletPool.clear();
	explosionPool.clear();
	experiencePool.clear();
}

std::shared_ptr<Bullet> GameObjectFactory::acquireBullet(sf::Vector2f direction, int damage)
{
	std::shared_ptr<Bullet> newBullet = std::dynamic_pointer_cast<Bullet>(getPooledObject(O_Bullet));
	newBullet->reinitialize(direction, damage);
	return newBullet;
}

std::shared_ptr<Asteroid> GameObjectFactory::acquireAsteroid(sf::Vector2f direction, float scale, float speed, float rotationSpeed)
{
	std::shared_ptr<Asteroid> newAsteroid = std::dynamic_pointer_cast<Asteroid>(getPooledObject(O_Asteroid));
	newAsteroid->reinitialize(direction, scale, speed, rotationSpeed);
	return newAsteroid;
}

std::shared_ptr<Explosion> GameObjectFactory::acquireExplosion(sf::Time duration, float scale, sf::Color tint)
{
	std::shared_ptr<Explosion> newExplosion = std::dynamic_pointer_cast<Explosion>(getPooledObject(O_Explosion));
	newExplosion->reinitialize(duration, scale, tint);
	return newExplosion;
}

std::shared_ptr<Experience> GameObjectFactory::acquireExperience(int amount)
{
	std::shared_ptr<Experience> newExperience = std::dynamic_pointer_cast<Experience>(getPooledObject(O_Experience));
	newExperience->reinitialize(amount);
	return newExperience;
}

std::shared_ptr<GameObject> GameObjectFactory::getPooledObject(ObjectType type)
{
	std::optional<std::shared_ptr<GameObject>> storedObject;

	switch (type) {
	case O_Asteroid:
		storedObject = asteroidPool.acquireObject();
		break;
	case O_Bullet:
		storedObject = bulletPool.acquireObject();
		break;
	case O_Explosion:
		storedObject = explosionPool.acquireObject();
		break;
	case O_Experience:
		storedObject = experiencePool.acquireObject();
		break;
	}

	if (storedObject.has_value()) {
		return storedObject.value();
	} else {
		std::shared_ptr<GameObject> newObject;
		
		switch (type) {
		case O_Asteroid:
			newObject = std::make_shared<Asteroid>();
			break;
		case O_Bullet:
			newObject = std::make_shared<Bullet>();
			break;
		case O_Explosion:
			newObject = std::make_shared<Explosion>();
			break;
		case O_Experience:
			newObject = std::make_shared<Experience>();
			break;
		}

		newObject->initializeComponents();
		return newObject;
	}
}

void GameObjectFactory::fillPool(ObjectType type, int initialAmount)
{
	while (initialAmount > 0)
	{
		std::shared_ptr<GameObject> newObject;

		switch (type) {
		case O_Asteroid:
			newObject = std::make_shared<Asteroid>();
			break;
		case O_Bullet:
			newObject = std::make_shared<Bullet>();
			break;
		case O_Explosion:
			newObject = std::make_shared<Explosion>();
			break;
		case O_Experience:
			newObject = std::make_shared<Experience>();
			break;
		}

		newObject->initializeComponents();

		switch (type) {
		case O_Asteroid:
			asteroidPool.releaseObject(std::dynamic_pointer_cast<Asteroid>(newObject));
			break;
		case O_Bullet:
			bulletPool.releaseObject(std::dynamic_pointer_cast<Bullet>(newObject));
			break;
		case O_Explosion:
			explosionPool.releaseObject(std::dynamic_pointer_cast<Explosion>(newObject));
			break;
		case O_Experience:
			experiencePool.releaseObject(std::dynamic_pointer_cast<Experience>(newObject));
			break;
		}

		initialAmount--;
	}
	
}

void GameObjectFactory::onEvent(const Event event)
{
	switch (event.type) {
	case Event::GRID_OBJECT_DESPAWNED:
	case Event::GRID_OBJECT_OUT_OF_BOUNDS:
		GameObjectWrapper despawnedObject = std::get<GameObjectWrapper>(event.info);

		switch (despawnedObject.ref->type) {
		case O_Asteroid:
			asteroidPool.releaseObject(std::dynamic_pointer_cast<Asteroid>(despawnedObject.ref));
			break;
		case O_Bullet:
			bulletPool.releaseObject(std::dynamic_pointer_cast<Bullet>(despawnedObject.ref));
			break;
		case O_Explosion:
			explosionPool.releaseObject(std::dynamic_pointer_cast<Explosion>(despawnedObject.ref));
			break;
		case O_Experience:
			experiencePool.releaseObject(std::dynamic_pointer_cast<Experience>(despawnedObject.ref));
			break;
		}
		break;
	}
}
