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

	std::cout << scale << std::endl;

	collider = Collider(this, sprite.getTextureRect().getSize().x - 4, sprite.getTextureRect().getSize().y - 4);
	collider.setOrigin(-2, -2);

	totalHitPoins = 10 * scale;
	currentHitPoints = totalHitPoins;
}

void Asteroid::update(sf::Time deltaTime) 
{
	sf::Color currentColor = sprite.getColor();
	float tintFactor = float(currentHitPoints) / float(totalHitPoins);
	sprite.setColor(sf::Color(currentColor.r, 255 * tintFactor, 255 * tintFactor));

	if (currentHitPoints <= 0) {
		markForDespawn();
	}

	GameObject::update(deltaTime);
}

void Asteroid::interact(Interaction action, GameObject& interactor)
{
	switch (action) {
	case Interaction::BulletCollision:
		sf::Vector2f direction = VectorExtension::toUnitVector(interactor.getRotation());
		controller->applyForce(direction * 50.f);
		currentHitPoints -= 10;
		break;
	}
}

void Asteroid::setDirection(sf::Vector2f direction)
{

}
