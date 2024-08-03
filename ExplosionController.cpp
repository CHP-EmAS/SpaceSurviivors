#include "ExplosionController.h"

#include "GameObject.h"
#include "SpriteRenderer.h"

ExplosionController::ExplosionController(std::shared_ptr<GameObject> parent) : Component(parent)
{
	explosionDuration = 0;
	explosionTimer = 0;
	explosionFrame = 0;
	frameInterval = explosionDuration * 0.1;
}

void ExplosionController::onUpdate(const sf::Time& deltaTime)
{
	if (auto parent = _parent.lock()) {
		explosionTimer += deltaTime.asSeconds();

		sf::Sprite* expSprite = parent->getComponent<SpriteRenderer>()->getSprite();

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
				parent->despawn();
				break;
			}

			explosionTimer = 0;
		}
	}
}
