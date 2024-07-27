#include "Bullet.h"
#include "Locator.h"
#include "VectorExtension.h"
#include "Event.h"
#include "CircleCollider.h"
#include "SpriteRenderer.h"

Bullet::Bullet() : GameObject(ObjectType::O_Bullet)
{
	owner = std::shared_ptr<GameObject>();
	speed = 1200.f;
	damage = 0;
	
	setScale(0.666f, 0.666f);

	std::cout << "Bullet created" << std::endl;
}

Bullet::~Bullet()
{
	std::cout << "Bullet deleted" << std::endl;
}

void Bullet::initializeComponents()
{
	SpriteRenderer spriteRenderer(shared_from_this());
	CircleCollider collider(shared_from_this(), 6);

	sf::Sprite bulletSprite(Locator::getGraphicService().getTexture(GraphicService::Bullets));
	bulletSprite.setTextureRect(sf::IntRect(64, 0, 20, 10));
	spriteRenderer.setSprite(bulletSprite);

	sf::Vector2f origin = sf::Vector2f(bulletSprite.getTextureRect().getSize().x / 2, bulletSprite.getTextureRect().getSize().y / 2);
	setOrigin(origin);
	collider.setPosition(origin + sf::Vector2f(4, 0));

	registerComponent(std::make_unique<SpriteRenderer>(spriteRenderer));
	registerComponent(std::make_unique<CircleCollider>(collider));
}

void Bullet::reinitialize(sf::Vector2f direction, int damage)
{
	this->damage = damage;
	this->direction = direction;

	setRotation(getAngle(direction));
}

void Bullet::shotBy(std::shared_ptr<GameObject> owner)
{
	this->owner = owner;
}

void Bullet::update(sf::Time deltaTime, GameState& state)
{
	//move
	move(direction * speed * deltaTime.asSeconds());
	
	//collision
	bool collsion = false;
	std::vector<std::shared_ptr<GameObject>> collidingObjects = Locator::getGameWorld().getCollisionLayer().getCollidingObjects(shared_from_this());

	while (collidingObjects.size() > 0) {
		auto& collidingObject = collidingObjects.back();

		if (owner.lock().get() != collidingObject.get()) {
			collidingObject->interact(Event(Event::BulletCollision,shared_from_this()));
			collsion = true;
		}

		collidingObjects.pop_back();
	}

	if (collsion) {
		despawn();
	}
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	getComponent<SpriteRenderer>()->draw(target, states);

#if _DEBUG
	getComponent<CircleCollider>()->debugDraw(target, states);
#endif
}


