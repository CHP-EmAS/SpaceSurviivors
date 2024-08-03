#include "ExperienceController.h"

#include "VectorExtension.h"
#include "RigidBody.h"
#include "GameObject.h"

ExperienceController::ExperienceController(std::shared_ptr<GameObject> parent) : Component(parent) 
{
	amount = 0;
	collectionSpeed = -0.25;
	moveToTarget = false;
	circle.setFillColor(sf::Color::Green);
	circle.setRadius(3.f);
}

void ExperienceController::onUpdate(const sf::Time& deltaTime)
{
	if (auto parent = _parent.lock()) {
		if (!moveToTarget || target.expired()) {
			return;
		}


		sf::Vector2f direction = target.lock()->getPosition() - parent->getPosition();
		sf::Vector2f newVelocity = normalize(direction) * collectionSpeed * 600.f;

		if (vectorSquareLength(newVelocity * deltaTime.asSeconds()) >= vectorSquareLength(direction)) {
			parent->despawn();
			//TODO EXPERIENCE COLLISION
		}
		else {
			RigidBody* rigidBody = parent->getComponent<RigidBody>();
			rigidBody->setVelocity(newVelocity);
			collectionSpeed += deltaTime.asSeconds();
		}
	}
}

void ExperienceController::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(circle, states);
}
