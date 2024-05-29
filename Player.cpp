#include "Player.h"
#include "Locator.h"

#include "VectorExtension.h"
#include "PlayerController.h"

Player::Player(BulletPool* bulletPool) : GameObject(ObjectType::O_Player)
{
	this->bulletPool = bulletPool;

	sprite.setTexture(Locator::getGraphicService().getTexture(GraphicService::Player));
	bulletSpawnPoint.x = sprite.getTextureRect().getSize().x - 5;
	bulletSpawnPoint.y = static_cast<float>(sprite.getTextureRect().getSize().y) / 2.f;

	sf::Vector2f origin = sf::Vector2f(sprite.getTextureRect().getSize().x / 2 - 5, sprite.getTextureRect().getSize().y / 2);
	setOrigin(origin);
	setScale(1.5, 1.5);
	
	collider = Collider(this, sf::Vector2f(sprite.getTextureRect().getSize().x - 5, sprite.getTextureRect().getSize().y - 15));
	collider.setOrigin(0, -7.5);

	setController(new PlayerController(this));

	timeSinceLastShot = 0.f;
	shootInterval = 0.1;

	invincibleTimer = 0;
	flicker = false;
	flickerTimer = 0;
}

void Player::interact(Interaction action, GameObject& interactor)
{
	switch (action) {
	case Interaction::AsteroidCollision:
		controller->applyForce(interactor.getController()->getCurrentVelocity() * 100.f);
		interactor.markForDespawn();
		break;
	}
}

void Player::update(sf::Time deltaTime, GameState& state)
{
	GameObject::update(deltaTime, state);

	timeSinceLastShot += deltaTime.asSeconds();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timeSinceLastShot >= shootInterval) {
		Bullet* newBullet = bulletPool->getNewBullet();
		
		sf::Vector2f spawn = getTransform().transformPoint(bulletSpawnPoint);
		newBullet->setOwner(this);
		newBullet->setPosition(spawn);
		newBullet->setRotation(getRotation());
	
		controller->applyForce(VectorExtension::toUnitVector(getRotation() - 180.f) * 50.f);
		
		timeSinceLastShot = 0;
	}

	if (!isInvincible()) {
		checkCollisions();
	}
	

	if (isInvincible()) {
		updateInvincibility(deltaTime);
	}
	else if(flicker) {
		setFlicker(false);
	}
	
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	GameObject::draw(target, states);
}

void Player::setInvincibility(sf::Time duration)
{
	invincibleTimer = duration.asSeconds();
	flickerTimer = 0;
}

bool Player::isInvincible()
{
	return invincibleTimer > 0;
}

void Player::checkCollisions()
{
	std::vector<GameObject*> collidingObjects = grid->getCollidingObjects(this);

	while (collidingObjects.size() > 0) {
		GameObject* collidingObject = collidingObjects.back();

		if (collidingObject->getType() == O_Asteroid) {
			Controller* asteroidController = collidingObject->getController();

			if (asteroidController) {
				sf::Vector2f asteroidVelocity = asteroidController->getCurrentVelocity();
				sf::Vector2f explodeDirection = collidingObject->getPosition();

				float speed = std::sqrt(VectorExtension::vectorSquareLength(asteroidVelocity * 20.f));
				explodeDirection = VectorExtension::normalize(getPosition() - explodeDirection);

				controller->applyForce(explodeDirection * speed);
				setInvincibility(sf::seconds(1.5));
			}

			collidingObject->interact(PlayerCollision, *this);
		}

		collidingObjects.pop_back();
	}
}

void Player::updateInvincibility(sf::Time deltaTime)
{
	invincibleTimer -= deltaTime.asSeconds();
	flickerTimer -= deltaTime.asSeconds();

	if (flickerTimer <= 0) {
		setFlicker(!flicker);
		flickerTimer = 0.12;
	}
}

void Player::setFlicker(bool flicker)
{
	this->flicker = flicker;

	if (flicker) {
		sprite.setColor(sf::Color(255, 50, 50, 100));
	} else {
		sprite.setColor(sf::Color::White);
	}
}
