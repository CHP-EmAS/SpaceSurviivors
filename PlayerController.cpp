#include "PlayerController.h"
#include "Player.h"

#include "Locator.h"
#include "GameState.h"

#include "VectorExtension.h"

#include "SpriteRenderer.h"
#include "RigidBody.h"
#include "CircleCollider.h"

PlayerController::PlayerController(std::shared_ptr<GameObject> parent) : Component(parent)
{
	gameOverExplosionTimer = 0.f;
	timeSinceLastShot = 0.f;
	invincibleTimer = 0.f;
	flicker = false;
	flickerTimer = 0.f;
}

void PlayerController::onEvent(const Event& event)
{
	if (auto parent = _parent.lock()) {
		switch (event.type) {
		case EventType::ASTEROID_COLLISION:
			GameObjectEventInfo objectInfo = std::get<GameObjectEventInfo>(event.info);
			std::shared_ptr<Asteroid> collidingAsteroid = std::static_pointer_cast<Asteroid>(objectInfo.ref);
			
			RigidBody* asteroidRigidBody = collidingAsteroid->getComponent<RigidBody>();
			if (asteroidRigidBody) {
				parent->getComponent<RigidBody>()->applyForce(asteroidRigidBody->getCurrentVelocity() * 100.f);
			}
			collidingAsteroid->despawn();
			break;
		}
	}
}

void PlayerController::onUpdate(const sf::Time& deltaTime)
{
	if (auto parent = _parent.lock()) {
		auto state = Locator::get<GameState>();

		if (state->isGameOver()) {
			playGameOverAnimation(deltaTime);
			return;
		}

		timeSinceLastShot += deltaTime.asSeconds();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timeSinceLastShot >= (1.f / state->getPlayerShotsPerSecond())) {
			shootBullet(state->getPlayerDamage());
			timeSinceLastShot = 0;
		}

		if (!isInvincible()) {
			if (checkCollisions()) {
				setInvincibility(sf::seconds(state->getPlayerInvinciblyInterval()));
				state->decreaseHealthBy(1);
			}
		}

		if (isInvincible()) {
			updateInvincibility(deltaTime);
		}
		else if (flicker) {
			setFlicker(false);
		}
	}
}

void PlayerController::setInvincibility(sf::Time duration)
{
	invincibleTimer = duration.asSeconds();
	flickerTimer = 0;
}

bool PlayerController::isInvincible() const
{
	return invincibleTimer > 0;
}

void PlayerController::playGameOverAnimation(const sf::Time& deltaTime)
{
	if (auto parent = _parent.lock()) {
		if (flicker) {
			setFlicker(false);
		}

		gameOverExplosionTimer -= deltaTime.asSeconds();

		if (gameOverExplosionTimer <= 0.f) {
			sf::Time explosionDuration = sf::Time(sf::seconds(0.8f));
			float explosionScale = parent->getScale().x + (float)(rand() % 160) / 100.f;
			sf::Color explosionColor = sf::Color(255, 150, 150);

			std::shared_ptr<Explosion> newExplosion = Locator::get<GameObjectFactory>()->acquireExplosion(explosionDuration, explosionScale, explosionColor);

			sf::Vector2f offset = sf::Vector2f(rand() % 50 - 25, rand() % 50 - 25);
			Locator::get<World>()->spawnObject(newExplosion, parent->getPosition() - offset);

			gameOverExplosionTimer = 0.8f;

			sf::Sprite* playerSprite = parent->getComponent<SpriteRenderer>()->getSprite();
			playerSprite->setColor(playerSprite->getColor() - sf::Color(20, 20, 20, 10));
		}
	}
}

bool PlayerController::checkCollisions()
{
	bool enemyCollision = false;
	std::shared_ptr<CollisionGrid> collisionGrid = Locator::get<CollisionGrid>();

	if (auto parent = _parent.lock()) {
		std::unordered_set<std::shared_ptr<GameObject>> collidingObjects = collisionGrid->getCollidingObjects(parent, G_DYNAMIC);

		for (auto& collidingObject : collidingObjects) {

			if (collidingObject->type == O_Asteroid) {
				enemyCollision = true;

				RigidBody* asteroidRigidBody = collidingObject->getComponent<RigidBody>();
				if (asteroidRigidBody) {
					sf::Vector2f asteroidVelocity = asteroidRigidBody->getCurrentVelocity();
					sf::Vector2f explodeDirection = collidingObject->getPosition();

					float speed = std::sqrt(vectorSquareLength(asteroidVelocity * 20.f));
					explodeDirection = normalize(parent->getPosition() - explodeDirection);

					parent->getComponent<RigidBody>()->applyForce(explodeDirection * speed);
				}

				collidingObject->interact(Event(EventType::PLAYER_COLLISION, parent));
			}
		}


		//TODO make this better XD
		CircleCollider collider(parent, 200);
		collider.onUpdate(sf::Time::Zero);

		collidingObjects = collisionGrid->getCollidingObjects(collider, G_STATIC);

		for (auto& collidingObject : collidingObjects) {
			if (collidingObject->type == O_Experience) {
				std::shared_ptr<Experience> exp = std::static_pointer_cast<Experience>(collidingObject);
				exp->trigger(parent);
			}
		}
	}

	return enemyCollision;
}

void PlayerController::updateInvincibility(const sf::Time& deltaTime)
{
	invincibleTimer -= deltaTime.asSeconds();
	flickerTimer -= deltaTime.asSeconds();

	if (flickerTimer <= 0) {
		setFlicker(!flicker);
		flickerTimer = 0.12f;
	}
}

void PlayerController::setFlicker(bool flicker)
{
	if (auto parent = _parent.lock()) {
		this->flicker = flicker;

		if (flicker) {
			parent->getComponent<SpriteRenderer>()->getSprite()->setColor(sf::Color(255, 50, 50, 100));
		}
		else {
			parent->getComponent<SpriteRenderer>()->getSprite()->setColor(sf::Color::White);
		}
	}
}

void PlayerController::shootBullet(int bulletDamage)
{
	if (auto parent = _parent.lock()) {
		sf::Vector2f bulletDirection = toUnitVector(parent->getRotation());

		std::shared_ptr<Bullet> newBullet = Locator::get<GameObjectFactory>()->acquireBullet(bulletDirection, bulletDamage);

		sf::Vector2f spawnPoint = parent->getTransform().transformPoint(bulletSpawnPoint);
		Locator::get<World>()->spawnObject(newBullet, spawnPoint);

		parent->getComponent<RigidBody>()->applyForce(toUnitVector(parent->getRotation() - 180.f) * 50.f);
	}
}
