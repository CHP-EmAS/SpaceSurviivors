#include "Explosion.h"

#include "Locator.h"
#include "SpriteRenderer.h"

Explosion::Explosion() : GameObject(ObjectType::O_Explosion)
{
	explosionDuration = 0;
	explosionTimer = 0;
	explosionFrame = 0;
	frameInterval = explosionDuration * 0.1;

	std::cout << "Explosion created" << std::endl;
}

Explosion::~Explosion()
{
	std::cout << "Explosion deleted" << std::endl;
}

void Explosion::initializeComponents()
{
	sf::Sprite explosionSprite(Locator::getGraphicService().getTexture(GraphicService::ExplosionAnimation));
	explosionSprite.setTextureRect(sf::IntRect(3, 36, 14, 14));
	explosionSprite.setOrigin(7, 7);

	SpriteRenderer spriteRenderer(shared_from_this());
	spriteRenderer.setSprite(explosionSprite);

	registerComponent(std::make_unique<SpriteRenderer>(spriteRenderer));
}

void Explosion::reinitialize(sf::Time duration, float scale, sf::Color tint)
{
	explosionDuration = duration.asSeconds();
	explosionTimer = 0;
	explosionFrame = 0;
	frameInterval = explosionDuration * 0.1;

	SpriteRenderer* renderer = getComponent<SpriteRenderer>();
	renderer->getSprite()->setScale(scale, scale);
	renderer->getSprite()->setColor(tint);
}

void Explosion::update(sf::Time deltaTime, GameState& state)
{
	explosionTimer += deltaTime.asSeconds();

	sf::Sprite *expSprite = getComponent<SpriteRenderer>()->getSprite();

	if (explosionTimer >= frameInterval) {
		explosionFrame++;

		switch (explosionFrame) {
		case 1: //10%
			expSprite->setTextureRect(sf::IntRect(20, 25, 30, 30));
			expSprite->setOrigin(15, 15);
			break;
		case 2: //20%
			expSprite->setTextureRect(sf::IntRect(53, 24, 30, 32));
			expSprite->setOrigin(14.5, 15.5);
			break;
		case 3: //30%
			expSprite->setTextureRect(sf::IntRect(86, 16, 44, 46));
			expSprite->setOrigin(21.5, 22.5);
			break;
		case 4: //40%
			expSprite->setTextureRect(sf::IntRect(133, 26, 28, 30));
			expSprite->setOrigin(14, 15);
			break;
		case 5: //50%
			expSprite->setTextureRect(sf::IntRect(164, 20, 39, 39));
			expSprite->setOrigin(19, 19);
			frameInterval = explosionDuration * 0.17;
			break;
		case 6: //67%
			expSprite->setTextureRect(sf::IntRect(206, 18, 42, 41));
			expSprite->setOrigin(21, 20);
			break;
		case 7: //84%
			expSprite->setTextureRect(sf::IntRect(251, 18, 43, 41));
			expSprite->setOrigin(21.5, 20);
			frameInterval = explosionDuration * 0.16;
			break;
		case 8: //100%
			despawn();
			break;
		}

		explosionTimer = 0;
	}
}

void Explosion::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	getComponent<SpriteRenderer>()->draw(target, states);
}


