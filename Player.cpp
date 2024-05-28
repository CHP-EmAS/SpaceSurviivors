#include "Player.h"
#include "Locator.h"

#include "VectorExtension.h"
#include "PlayerController.h"

Player::Player(BulletPool* bulletPool) : GameObject(ObjectType::O_Player)
{
	this->bulletPool = bulletPool;

	sprite.setTexture(Locator::getGraphicService().getTexture(GraphicService::Player));
	bulletSpawnPoint.x = sprite.getTextureRect().getSize().x;
	bulletSpawnPoint.y = static_cast<float>(sprite.getTextureRect().getSize().y) / 2.f;

	sf::Vector2f origin = sf::Vector2f(sprite.getTextureRect().getSize().x / 2, sprite.getTextureRect().getSize().y / 2);
	setOrigin(origin);

	collider = Collider(this, sf::Vector2f(sprite.getTextureRect().getSize().x, sprite.getTextureRect().getSize().y));

	setController(new PlayerController(this));

	timeSinceLastShot = 0.f;
	shootInterval = 0.1;

	velocityLine[0].position = sf::Vector2f(0, 0);
	velocityLine[1].position = sf::Vector2f(0, 0);

	velocityLine[0].color = sf::Color::Red;
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

void Player::update(sf::Time deltaTime)
{
	GameObject::update(deltaTime);

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

	velocityLine[0].position = getPosition();
	velocityLine[1].position = getPosition() + controller->getCurrentVelocity();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	GameObject::draw(target, states);

	target.draw(velocityLine, 2, sf::Lines);
}
