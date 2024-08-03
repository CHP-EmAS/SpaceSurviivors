#include "Explosion.h"

#include "Locator.h"
#include "SpriteRenderer.h"
#include "ExplosionController.h"

Explosion::Explosion() : GameObject(ObjectType::O_Explosion)
{
	std::cout << "Explosion created" << std::endl;
}

Explosion::~Explosion()
{
	std::cout << "Explosion deleted" << std::endl;
}

void Explosion::initializeComponents()
{
	sf::Sprite explosionSprite(Locator::get<GraphicService>()->getTexture(GraphicService::ExplosionAnimation));
	explosionSprite.setTextureRect(sf::IntRect(3, 36, 14, 14));
	explosionSprite.setOrigin(7, 7);

	ExplosionController controller(shared_from_this());
	SpriteRenderer spriteRenderer(shared_from_this());
	spriteRenderer.setSprite(explosionSprite);

	registerComponent(std::make_unique<ExplosionController>(controller));
	registerComponent(std::make_unique<SpriteRenderer>(spriteRenderer));
}

void Explosion::reinitialize(sf::Time duration, float scale, sf::Color tint)
{
	ExplosionController* controller = getComponent<ExplosionController>();
	controller->explosionDuration = duration.asSeconds();
	controller->explosionTimer = 0;
	controller->explosionFrame = 0;
	controller->frameInterval = controller->explosionDuration * 0.1;

	SpriteRenderer* renderer = getComponent<SpriteRenderer>();
	renderer->getSprite()->setScale(scale, scale);
	renderer->getSprite()->setColor(tint);
}


