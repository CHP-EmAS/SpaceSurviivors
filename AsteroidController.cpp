#include "AsteroidController.h"

#include "VectorExtension.h"
#include "GameObject.h"

#include "Locator.h"

#include "SpriteRenderer.h"
#include "RigidBody.h"

AsteroidController::AsteroidController(std::shared_ptr<GameObject> parent) : Component(parent)
{
	rotationSpeed = 0;
	totalHitPoins = 1;
	currentHitPoints = totalHitPoins;
	scoreReward = 0;
	experienceReward = 0;
}

void AsteroidController::onEvent(const Event& event)
{
	switch (event.type) {
	case EventType::BULLET_COLLISION: {
		if (auto parent = _parent.lock()) {
			GameObjectEventInfo objectInfo = std::get<GameObjectEventInfo>(event.info);
			std::shared_ptr<Bullet> collidingBullet = std::static_pointer_cast<Bullet>(objectInfo.ref);

			sf::Vector2f direction = toUnitVector(collidingBullet->getRotation());
			parent->getComponent<RigidBody>()->applyForce(direction * 50.f);

			float damage = collidingBullet->getDamage();
			float damageRatio = damage / totalHitPoins;

			if (damage > currentHitPoints) {
				damageRatio = currentHitPoints / totalHitPoins;
			}

			auto state = Locator::get<GameState>();
			state->increaseScoreBy(round(scoreReward * damageRatio * 0.4f));
			state->increaseExperienceBy(round(experienceReward * damageRatio * 0.4f));

			currentHitPoints -= damage;

			SpriteRenderer* spriteRenderer = parent->getComponent<SpriteRenderer>();

			sf::Color currentColor = spriteRenderer->getSprite()->getColor();
			float tintFactor = float(currentHitPoints) / float(totalHitPoins);
			spriteRenderer->getSprite()->setColor(sf::Color(currentColor.r, 255 * tintFactor, 255 * tintFactor));
		}
		break;
	}
	case EventType::PLAYER_COLLISION: {
		explode();
		break;
	}
	}
}

void AsteroidController::onUpdate(const sf::Time& deltaTime)
{
	if (currentHitPoints <= 0) {
		auto state = Locator::get<GameState>();

		state->increaseScoreBy(round(scoreReward * 0.6f));
		state->increaseExperienceBy(round(experienceReward * 0.6f));
		explode();
	}

	if (auto parent = _parent.lock()) {
		parent->rotate(rotationSpeed * deltaTime.asSeconds());
	}
}

void AsteroidController::explode()
{
	if (auto parent = _parent.lock()) {
		std::shared_ptr<Explosion> newExplosion = Locator::get<GameObjectFactory>()->acquireExplosion(sf::Time(sf::seconds(0.8)), parent->getScale().x * 0.8);
		Locator::get<World>()->spawnObject(newExplosion, parent->getPosition());
		parent->despawn();
	}
}
