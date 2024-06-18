#include "Bullet.h"
#include "Locator.h"
#include "VectorExtension.h"

Bullet::Bullet() : GameObject(ObjectType::O_Bullet)
{
	this->next = nullptr;
	
	sprite.setTexture(Locator::getGraphicService().getTexture(GraphicService::Bullets));
	sprite.setTextureRect(sf::IntRect(64, 0, 20, 10));

	sf::Vector2f origin = sf::Vector2f(sprite.getTextureRect().getSize().x / 2, sprite.getTextureRect().getSize().y / 2);
	setOrigin(origin);

	collider = Collider(this, sprite.getTextureRect().getSize().x, sprite.getTextureRect().getSize().y);

	isActive = false;
	shotBy = nullptr;
	speed = 1200.f;
	damage = 0;
}

void Bullet::setDamage(int damage)
{
	if (damage > 0) {
		this->damage = damage;
	}
}

void Bullet::setOwner(GameObject* owner)
{
	shotBy = owner;
}

bool Bullet::bulletUpdate(sf::Time deltaTime)
{
	if (!isActive) {
		return false;
	}
	 
	sf::Vector2f position = getPosition();

	if (position.x > -50 && position.x < WINDOW_SIZE + 50 &&
		position.y > -50 && position.y < WINDOW_SIZE + 50) {

		sf::Vector2f direction = VectorExtension::toUnitVector(getRotation());

		move(direction * speed * deltaTime.asSeconds());
	} else {
		//deactivete bullet;
		return true;
	}

	bool collision = false;
	std::vector<GameObject*> collidingObjects = grid->getCollidingObjects(this);

	while(collidingObjects.size() > 0) {
		GameObject* collidingObject = collidingObjects.back();

		if (shotBy != collidingObject) {
			collidingObject->interact(BulletCollision, *this);
			collision = true;
		}
		
		collidingObjects.pop_back();
	}
	
	return collision;
}
