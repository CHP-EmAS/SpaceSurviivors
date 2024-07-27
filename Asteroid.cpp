#include "Asteroid.h"
#include "Locator.h"
#include "VectorExtension.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Game.h"
#include "Event.h"
#include "SpriteRenderer.h"
#include "RigidBody.h"
#include "Bullet.h"

Asteroid::Asteroid() : GameObject(ObjectType::O_Asteroid)
{
	this->rotationSpeed = 0;
	totalHitPoins = 1;
	currentHitPoints = totalHitPoins;
	scoreReward = 0;
	experienceReward = 0;

	std::cout << "Asteroid created" << std::endl;
}

Asteroid::~Asteroid()
{
	std::cout << "Asteroid deleted" << std::endl;
}

void Asteroid::initializeComponents()
{
	sf::Sprite asteroidSprite = sf::Sprite(Locator::getGraphicService().getTexture(GraphicService::Asteroid));
	sf::Vector2f origin = sf::Vector2f(asteroidSprite.getTextureRect().getSize().x / 2, asteroidSprite.getTextureRect().getSize().y / 2);

	setOrigin(origin);

	CircleCollider collider(shared_from_this(), 13);
	RigidBody rigidBody(shared_from_this());
	SpriteRenderer spriteRenderer(shared_from_this());

	spriteRenderer.setSprite(asteroidSprite);
	collider.setPosition(origin - sf::Vector2f(0, -1));

	registerComponent(std::make_unique<SpriteRenderer>(spriteRenderer));
	registerComponent(std::make_unique<CircleCollider>(collider));
	registerComponent(std::make_unique<RigidBody>(rigidBody));
}

void Asteroid::reinitialize(sf::Vector2f direction, float scale, float speed, float rotationSpeed)
{
	this->rotationSpeed = rotationSpeed;
	totalHitPoins = 10.f * scale;
	currentHitPoints = totalHitPoins;
	scoreReward = 100.f * scale;
	experienceReward = 5.f * scale;

	setScale(scale, scale);

	getComponent<RigidBody>()->setVelocity(normalize(direction) * speed);
	getComponent<SpriteRenderer>()->getSprite()->setColor(sf::Color(255, 255, 255));
}

void Asteroid::update(sf::Time deltaTime, GameState& state)
{
	if (currentHitPoints <= 0) {
		state.increaseScoreBy(round(scoreReward * 0.6f));
		state.increaseExperienceBy(round(experienceReward * 0.6f));
		explode();
	}

	rotate(rotationSpeed * deltaTime.asSeconds());

	getComponent<RigidBody>()->simulate(deltaTime);
}

void Asteroid::explode()
{
	std::shared_ptr<Explosion> newExplosion = Locator::getGameWorld().getGameObjectFactory().acquireExplosion(sf::Time(sf::seconds(0.8)), getScale().x * 0.8);
	newExplosion->spaw(getPosition(), L_Effect);

	despawn();
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	getComponent<SpriteRenderer>()->draw(target, states);

#if _DEBUG
	getComponent<CircleCollider>()->debugDraw(target, states);
	getComponent<RigidBody>()->debugDraw(target, states);
#endif

	
}

void Asteroid::interact(const Event event)
{
	switch (event.type) {
	case Event::BulletCollision: {
		GameObjectWrapper objectWrapper = std::get<GameObjectWrapper>(event.info);
		std::shared_ptr<Bullet> collidingBullet = std::dynamic_pointer_cast<Bullet>(objectWrapper.ref);

		sf::Vector2f direction = toUnitVector(collidingBullet->getRotation());
		getComponent<RigidBody>()->applyForce(direction * 50.f);

		float damage = collidingBullet->getDamage();
		float damageRatio = damage / totalHitPoins;

		if (damage > currentHitPoints) {
			damageRatio = currentHitPoints / totalHitPoins;
		}

		GameState& state = static_cast<GameScene*>(Locator::getSceneManager().getScene(Scene::Game))->getState();
		state.increaseScoreBy(round(scoreReward * damageRatio * 0.4f));
		state.increaseExperienceBy(round(experienceReward * damageRatio * 0.4f));

		currentHitPoints -= damage;

		SpriteRenderer* spriteRenderer = getComponent<SpriteRenderer>();

		sf::Color currentColor = spriteRenderer->getSprite()->getColor();
		float tintFactor = float(currentHitPoints) / float(totalHitPoins);
		spriteRenderer->getSprite()->setColor(sf::Color(currentColor.r, 255 * tintFactor, 255 * tintFactor));

		break;
	}
	case Event::PlayerCollision: {
		explode();
		break;
	}
	}
}
