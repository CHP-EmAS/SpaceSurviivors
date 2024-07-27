#include "Experience.h"

#include "VectorExtension.h"
#include "Locator.h"
#include "RigidBody.h"


Experience::Experience() : GameObject(O_Experience)
{
	amount = 0;
	collectionSpeed = -0.25;

	moveToTarget = false;

	circle.setFillColor(sf::Color::Green);
	circle.setRadius(3.f);

	std::cout << "Experience created" << std::endl;
}

Experience::~Experience()
{
	std::cout << "Experience deleted" << std::endl;
}

void Experience::initializeComponents()
{
	RigidBody rigidBody(shared_from_this());
	registerComponent(std::make_unique<RigidBody>(rigidBody));
}

void Experience::reinitialize(int amount)
{
	amount = 0;
	collectionSpeed = -0.25;

	target.reset();
	moveToTarget = false;
	
	getComponent<RigidBody>()->setVelocity(sf::Vector2f(0, 0));
}

void Experience::trigger(std::weak_ptr<GameObject> target)
{
	this->target = target;

	sf::Vector2f direction = normalize(target.lock()->getPosition() - getPosition());
	getComponent<RigidBody>()->setVelocity(-direction * 100.f);

	moveToTarget = true;
}

void Experience::update(sf::Time deltaTime, GameState& state)
{
	if (!moveToTarget || target.expired()) {
		return;
	}

	sf::Vector2f direction = normalize(target.lock()->getPosition() - getPosition());

	RigidBody* rigidBody = getComponent<RigidBody>();

	rigidBody->setVelocity(direction * collectionSpeed * 600.f);
	rigidBody->simulate(deltaTime);

	collectionSpeed += deltaTime.asSeconds();
}

bool Experience::isTriggerd() const
{
	return moveToTarget;
}

int Experience::getAmount() const
{
	return amount;
}

void Experience::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(circle, states);
}
