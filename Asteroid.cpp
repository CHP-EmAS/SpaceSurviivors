#include "Asteroid.h"
#include "AsteroidController.h"
#include "Locator.h"
#include "VectorExtension.h"
#include "SpatialPartitionGrid.h"

Asteroid::Asteroid(sf::Vector2f direction, float scale, float speed, float rotationSpeed) : GameObject(ObjectType::O_Asteroid)
{
	AsteroidController* controller = new AsteroidController(this, direction, speed, rotationSpeed);
	setController(controller);

	sprite.setTexture(Locator::getGraphicService().getTexture(GraphicService::Asteroid));
	sf::Vector2f origin = sf::Vector2f(sprite.getTextureRect().getSize().x / 2, sprite.getTextureRect().getSize().y / 2);
	setOrigin(origin);
	setScale(scale, scale);

	collider = Collider(this, sprite.getTextureRect().getSize().x - 4, sprite.getTextureRect().getSize().y - 4);
	collider.setOrigin(-2, -2);
}

void Asteroid::update(sf::Time deltaTime) {

	std::vector<GameObject*> collidingObjects = grid->getCollidingObjects(this);

	while (collidingObjects.size() > 0) {
		GameObject* collidingObject = collidingObjects.back();
		collidingObject->interact(AsteroidCollision, *this);
		collidingObjects.pop_back();
	}

	GameObject::update(deltaTime);
}

void Asteroid::interact(Interaction action, GameObject& interactor)
{
	switch (action) {
	case Interaction::BulletCollision:
		sf::Vector2f direction = VectorExtension::toUnitVector(interactor.getRotation());
		controller->applyForce(direction * 50.f);
		break;
	}
}

void Asteroid::setDirection(sf::Vector2f direction)
{

}
