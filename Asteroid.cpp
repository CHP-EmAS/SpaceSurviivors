#include "Asteroid.h"
#include "Locator.h"
#include "VectorExtension.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Game.h"
#include "Event.h"
#include "AsteroidController.h"
#include "SpriteRenderer.h"
#include "RigidBody.h"
#include "GridComponent.h"
#include "Bullet.h"
#include "GraphicService.h"

Asteroid::Asteroid() : GameObject(ObjectType::O_Asteroid)
{
	std::cout << "Asteroid created" << std::endl;
}

Asteroid::~Asteroid()
{
	std::cout << "Asteroid deleted" << std::endl;
}

void Asteroid::initializeComponents()
{
	sf::Sprite asteroidSprite = sf::Sprite(Locator::get<GraphicService>()->getTexture(GraphicService::Asteroid));
	sf::Vector2f origin = sf::Vector2f(asteroidSprite.getTextureRect().getSize().x / 2, asteroidSprite.getTextureRect().getSize().y / 2);

	setOrigin(origin);

	AsteroidController controller(shared_from_this());
	CircleCollider collider(shared_from_this(), 13);
	RigidBody rigidBody(shared_from_this());
	SpriteRenderer spriteRenderer(shared_from_this());
	GridComponent grid(shared_from_this(), G_DYNAMIC);

	spriteRenderer.setSprite(asteroidSprite);
	collider.setPosition(origin - sf::Vector2f(0, -1));

	registerComponent(std::make_unique<AsteroidController>(controller));
	registerComponent(std::make_unique<SpriteRenderer>(spriteRenderer));
	registerComponent(std::make_unique<CircleCollider>(collider));
	registerComponent(std::make_unique<RigidBody>(rigidBody));
	registerComponent(std::make_unique<GridComponent>(grid));
}

void Asteroid::reinitialize(sf::Vector2f direction, float scale, float speed, float rotationSpeed)
{
	AsteroidController* controller = getComponent<AsteroidController>();

	controller->rotationSpeed = rotationSpeed;
	controller->totalHitPoins = 10.f * scale;
	controller->currentHitPoints = controller->totalHitPoins;
	controller->scoreReward = 100.f * scale;
	controller->experienceReward = 5.f * scale;

	setScale(scale, scale);

	getComponent<RigidBody>()->setVelocity(normalize(direction) * speed);
	getComponent<SpriteRenderer>()->getSprite()->setColor(sf::Color(255, 255, 255));
}
