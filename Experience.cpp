#include "Experience.h"
#include "ExperienceController.h"

#include "VectorExtension.h"
#include "Locator.h"
#include "RigidBody.h"
#include "GridComponent.h"


Experience::Experience() : GameObject(O_Experience)
{
	std::cout << "Experience created" << std::endl;
}

Experience::~Experience()
{
	std::cout << "Experience deleted" << std::endl;
}

void Experience::initializeComponents()
{
	ExperienceController controller(shared_from_this());
	RigidBody rigidBody(shared_from_this());
	GridComponent grid(shared_from_this(), G_STATIC);

	registerComponent(std::make_unique<ExperienceController>(controller));
	registerComponent(std::make_unique<RigidBody>(rigidBody));
	registerComponent(std::make_unique<GridComponent>(grid));
}

void Experience::reinitialize(int amount)
{
	ExperienceController* controller = getComponent<ExperienceController>();
	controller->amount = 0;
	controller->collectionSpeed = -0.25;
	controller->target.reset();
	controller->moveToTarget = false;
	
	getComponent<RigidBody>()->setVelocity(sf::Vector2f(0, 0));
}

void Experience::trigger(std::weak_ptr<GameObject> target)
{
	ExperienceController* controller = getComponent<ExperienceController>();

	controller->target = target;

	sf::Vector2f direction = normalize(target.lock()->getPosition() - getPosition());
	getComponent<RigidBody>()->setVelocity(-direction * 100.f);
	
	controller->moveToTarget = true;

	getComponent<GridComponent>()->removeSelfFromCollisionGrid();
}

bool Experience::isTriggerd() const
{
	return getComponent<ExperienceController>()->moveToTarget;
}

int Experience::getAmount() const
{
	return getComponent<ExperienceController>()->amount;
}
