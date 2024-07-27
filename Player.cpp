#include "Player.h"
#include "Locator.h"

#include "VectorExtension.h"

#include "RigidBody.h"
#include "SpriteRenderer.h"
#include "PlayerInputComponent.h"
#include "BoxCollider.h"
#include "Explosion.h"

Player::Player() : GameObject(ObjectType::O_Player)
{
	gameOverExplosionTimer = 0.f;
	timeSinceLastShot = 0.f;
	invincibleTimer = 0.f;
	flicker = false;
	flickerTimer = 0.f;
}

void Player::initializeComponents()
{
	RigidBody rigidBody(shared_from_this());
	PlayerInputComponent input(shared_from_this());
	SpriteRenderer spriteRenderer(shared_from_this());
	BoxCollider collider(shared_from_this(), 35, 25);

	sf::Sprite playerSprite = sf::Sprite(Locator::getGraphicService().getTexture(GraphicService::Player));
	spriteRenderer.setSprite(playerSprite);

	rigidBody.setMaxSpeed(1800.f);
	rigidBody.setFriction(0.01f);
	rigidBody.setBoundingBox(sf::FloatRect(0, 0, WINDOW_SIZE, WINDOW_SIZE));

	sf::Vector2f origin = sf::Vector2f(playerSprite.getTextureRect().getSize().x / 2 - 5, playerSprite.getTextureRect().getSize().y / 2);
	setOrigin(origin);

	collider.setPosition(origin);

	registerComponent(std::make_unique<RigidBody>(rigidBody));
	registerComponent(std::make_unique<PlayerInputComponent>(input));
	registerComponent(std::make_unique<SpriteRenderer>(spriteRenderer));
	registerComponent(std::make_unique<BoxCollider>(collider));

	bulletSpawnPoint.x = playerSprite.getTextureRect().getSize().x - 5;
	bulletSpawnPoint.y = static_cast<float>(playerSprite.getTextureRect().getSize().y) / 2.f;
}

void Player::interact(const Event event)
{
	switch (event.type) {
	case Event::AsteroidCollision:
		GameObjectWrapper objectWrapper = std::get<GameObjectWrapper>(event.info);
		std::shared_ptr<Asteroid> collidingAsteroid = std::dynamic_pointer_cast<Asteroid>(objectWrapper.ref);

		RigidBody* asteroidRigidBody = collidingAsteroid->getComponent<RigidBody>();
		if (asteroidRigidBody) {
			getComponent<RigidBody>()->applyForce(asteroidRigidBody->getCurrentVelocity() * 100.f);
		}
		collidingAsteroid->despawn();
		break;
	}
}

void Player::update(const sf::Time deltaTime, GameState& state)
{
	if (state.isGameOver()) {
		playGameOverAnimation(deltaTime);
		return;
	}

	getComponent<PlayerInputComponent>()->checkInput(deltaTime);
	getComponent<RigidBody>()->simulate(deltaTime);

	timeSinceLastShot += deltaTime.asSeconds();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timeSinceLastShot >= (1.f / state.getPlayerShotsPerSecond())) {
		shootBullet(state.getPlayerDamage());
		timeSinceLastShot = 0;
	}
	
	if (!isInvincible()) {
		if (checkCollisions()) {
			setInvincibility(sf::seconds(state.getPlayerInvinciblyInterval()));
			state.decreaseHealthBy(1);
		}
	}
	
	if (isInvincible()) {
		updateInvincibility(deltaTime);
	} else if(flicker) {
		setFlicker(false);
	}
	
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	getComponent<SpriteRenderer>()->draw(target, states);

#if _DEBUG
	getComponent<BoxCollider>()->debugDraw(target, states);
	getComponent<RigidBody>()->debugDraw(target, states);
#endif
}

void Player::setInvincibility(sf::Time duration)
{
	invincibleTimer = duration.asSeconds();
	flickerTimer = 0;
}

bool Player::isInvincible() const
{
	return invincibleTimer > 0;
}

void Player::playGameOverAnimation(sf::Time deltaTime)
{
	if (flicker) {
		setFlicker(false);
	}

	gameOverExplosionTimer -= deltaTime.asSeconds();

	if (gameOverExplosionTimer <= 0.f) {
		sf::Time explosionDuration = sf::Time(sf::seconds(0.8f));
		float explosionScale = getScale().x + (float)(rand() % 160) / 100.f;
		sf::Color explosionColor = sf::Color(255, 150, 150);

		std::shared_ptr<Explosion> newExplosion = Locator::getGameWorld().getGameObjectFactory()
			.acquireExplosion(explosionDuration, explosionScale, explosionColor);
		
		sf::Vector2f offset = sf::Vector2f(rand() % 50 - 25, rand() % 50 - 25);
		newExplosion->spaw(getPosition() - offset, L_Effect);

		gameOverExplosionTimer = 0.8f;

		sf::Sprite* playerSprite = getComponent<SpriteRenderer>()->getSprite();
		playerSprite->setColor(playerSprite->getColor() - sf::Color(20, 20, 20, 10));
	}
}

bool Player::checkCollisions()
{
	bool enemyCollision = false;
	std::vector<std::shared_ptr<GameObject>> collidingObjects = Locator::getGameWorld().getCollisionLayer().getCollidingObjects(shared_from_this());
	
	while (collidingObjects.size() > 0) {
		auto& collidingObject = collidingObjects.back();

		if (collidingObject->type == O_Asteroid) {
			enemyCollision = true;

			RigidBody* asteroidRigidBody = collidingObject->getComponent<RigidBody>();
			if (asteroidRigidBody) {
				sf::Vector2f asteroidVelocity = asteroidRigidBody->getCurrentVelocity();
				sf::Vector2f explodeDirection = collidingObject->getPosition();

				float speed = std::sqrt(vectorSquareLength(asteroidVelocity * 20.f));
				explodeDirection = normalize(getPosition() - explodeDirection);

				getComponent<RigidBody>()->applyForce(explodeDirection * speed);
			}

			collidingObject->interact(Event::Event(Event::PlayerCollision, std::dynamic_pointer_cast<Player>(shared_from_this())));
		}

		collidingObjects.pop_back();
	}

	std::vector<std::shared_ptr<Experience>> collidingExperience = Locator::getGameWorld().getCollisionLayer().collectExperiences(shared_from_this(), 100, 30);

	while (collidingExperience.size() > 0) {
		collidingExperience.pop_back();
	}

	return enemyCollision;
}

void Player::updateInvincibility(sf::Time deltaTime)
{
	invincibleTimer -= deltaTime.asSeconds();
	flickerTimer -= deltaTime.asSeconds();

	if (flickerTimer <= 0) {
		setFlicker(!flicker);
		flickerTimer = 0.12f;
	}
}

void Player::setFlicker(bool flicker)
{
	this->flicker = flicker;

	if (flicker) {
		getComponent<SpriteRenderer>()->getSprite()->setColor(sf::Color(255, 50, 50, 100));
	} else {
		getComponent<SpriteRenderer>()->getSprite()->setColor(sf::Color::White);
	}
}

void Player::shootBullet(int bulletDamage)
{
	sf::Vector2f bulletDirection = toUnitVector(getRotation());

	std::shared_ptr<Bullet> newBullet = Locator::getGameWorld().getGameObjectFactory()
		.acquireBullet(bulletDirection, bulletDamage);

	sf::Vector2f spawnPoint = getTransform().transformPoint(bulletSpawnPoint);
	newBullet->spaw(spawnPoint, L_Effect);

	getComponent<RigidBody>()->applyForce(toUnitVector(getRotation() - 180.f) * 50.f);
}
