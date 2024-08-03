#include "BulletController.h"

#include "Locator.h"
#include "GameObject.h"

BulletController::BulletController(std::shared_ptr<GameObject> parent) : Component(parent)
{
	owner = std::shared_ptr<GameObject>();
	speed = 1200.f;
	damage = 0;
}

void BulletController::onUpdate(const sf::Time& deltaTime)
{
	if (auto parent = _parent.lock()) {
		parent->move(direction * speed * deltaTime.asSeconds());

		//collision
		bool collsion = false;
		std::unordered_set<std::shared_ptr<GameObject>> collidingObjects = Locator::get<CollisionGrid>()->getCollidingObjects(parent, GRID::G_DYNAMIC);

		for (auto& collidingObject : collidingObjects) {
			if (owner.lock().get() != collidingObject.get()) {
				collidingObject->interact(Event(EventType::BULLET_COLLISION, parent));
				collsion = true;
			}
		}

		if (collsion) {
			parent->despawn();
		}
	}
}
