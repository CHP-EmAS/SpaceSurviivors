#include "Bullet.h"
#include "Locator.h"
#include "VectorExtension.h"
#include "Event.h"
#include "CircleCollider.h"
#include "SpriteRenderer.h"
#include "BulletController.h"

Bullet::Bullet() : GameObject(ObjectType::O_Bullet)
{
	setScale(0.666f, 0.666f);

	std::cout << "Bullet created" << std::endl;
}

Bullet::~Bullet()
{
	std::cout << "Bullet deleted" << std::endl;
}

void Bullet::initializeComponents()
{
	BulletController controller(shared_from_this());
	SpriteRenderer spriteRenderer(shared_from_this());
	CircleCollider collider(shared_from_this(), 6);

	sf::Sprite bulletSprite(Locator::get<GraphicService>()->getTexture(GraphicService::Bullets));
	bulletSprite.setTextureRect(sf::IntRect(64, 0, 20, 10));
	spriteRenderer.setSprite(bulletSprite);

	sf::Vector2f origin = sf::Vector2f(bulletSprite.getTextureRect().getSize().x / 2, bulletSprite.getTextureRect().getSize().y / 2);
	setOrigin(origin);
	collider.setPosition(origin + sf::Vector2f(4, 0));

	registerComponent(std::make_unique<BulletController>(controller));
	registerComponent(std::make_unique<SpriteRenderer>(spriteRenderer));
	registerComponent(std::make_unique<CircleCollider>(collider));
}

void Bullet::reinitialize(sf::Vector2f direction, int damage)
{
	BulletController* controller = getComponent<BulletController>();

	controller->damage = damage;
	controller->direction = direction;

	setRotation(getAngle(direction));
}

void Bullet::shotBy(std::shared_ptr<GameObject> owner)
{
	getComponent<BulletController>()->owner = owner;
}

int Bullet::getDamage() const
{
	return getComponent<BulletController>()->damage;
}


