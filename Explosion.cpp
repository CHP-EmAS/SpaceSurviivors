#include "Explosion.h"
#include "Locator.h"

Explosion::Explosion(float scale, sf::Time duration, sf::Color tint) : GameObject(ObjectType::O_Explosion)
{
	sprite.setTexture(Locator::getGraphicService().getTexture(GraphicService::ExplosionAnimation));
	sprite.setTextureRect(sf::IntRect(3, 36, 14, 14));
	sprite.setOrigin(7, 7);
	sprite.setScale(scale, scale);
	sprite.setColor(tint);

	collider.setSize(0, 0);

	explosionDuration = duration.asSeconds();
	explosionTimer = 0;
	explosionFrame = 0;
	frameInterval = explosionDuration * 0.1;
}

void Explosion::update(sf::Time deltaTime, GameState& state)
{
	explosionTimer += deltaTime.asSeconds();

	if (explosionTimer >= frameInterval) {
		explosionFrame++;

		switch (explosionFrame) {
		case 1: //10%
			sprite.setTextureRect(sf::IntRect(20, 25, 30, 30));
			sprite.setOrigin(15, 15);
			break;
		case 2: //20%
			sprite.setTextureRect(sf::IntRect(53, 24, 30, 32));
			sprite.setOrigin(14.5, 15.5);
			break;
		case 3: //30%
			sprite.setTextureRect(sf::IntRect(86, 16, 44, 46));
			sprite.setOrigin(21.5, 22.5);
			break;
		case 4: //40%
			sprite.setTextureRect(sf::IntRect(133, 26, 28, 30));
			sprite.setOrigin(14, 15);
			break;
		case 5: //50%
			sprite.setTextureRect(sf::IntRect(164, 20, 39, 39));
			sprite.setOrigin(19, 19);
			frameInterval = explosionDuration * 0.17;
			break;
		case 6: //67%
			sprite.setTextureRect(sf::IntRect(206, 18, 42, 41));
			sprite.setOrigin(21, 20);
			break;
		case 7: //84%
			sprite.setTextureRect(sf::IntRect(251, 18, 43, 41));
			sprite.setOrigin(21.5, 20);
			frameInterval = explosionDuration * 0.16;
			break;
		case 8: //100%
			markForDespawn();
			break;
		}

		explosionTimer = 0;
	}
}
