#include "Asteroid.h"
#include "AsteroidController.h"
#include "Locator.h"
#include "VectorExtension.h"
#include "SpatialPartitionGrid.h"
#include "Explosion.h"

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

	totalHitPoins = 10 * scale;
	currentHitPoints = totalHitPoins;
}

void Asteroid::update(sf::Time deltaTime, GameState& state)
{
	sf::Color currentColor = sprite.getColor();
	float tintFactor = float(currentHitPoints) / float(totalHitPoins);
	sprite.setColor(sf::Color(currentColor.r, 255 * tintFactor, 255 * tintFactor));

	if (currentHitPoints <= 0) {
		state.addScore(100 * getScale().x);
		explode();
	}

	GameObject::update(deltaTime, state);
}

void Asteroid::interact(Interaction action, GameObject& interactor)
{
	switch (action) {
	case Interaction::BulletCollision: {
		sf::Vector2f direction = VectorExtension::toUnitVector(interactor.getRotation());
		controller->applyForce(direction * 50.f);
		currentHitPoints -= 10;
		break;
	}
	case Interaction::PlayerCollision: {
		explode();
		break;
	}
	}
}

void Asteroid::explode()
{
	if (grid) {
		Explosion* newExplosion = new Explosion(getScale().x * 0.8, sf::Time(sf::seconds(0.8)));
		newExplosion->spawOnGrid(grid, getPosition());
	}

	markForDespawn();
}
