#include "CircleCollider.h"

#include "Locator.h"
#include "BoxCollider.h"
#include "VectorExtension.h"


CircleCollider::CircleCollider() :
	CircleCollider(nullptr, 0) {}

CircleCollider::CircleCollider(std::shared_ptr<GameObject> parent, float radius) : Component(parent)
{
	drawCircle.setFillColor(sf::Color(255, 255, 0, 130));
	setRadius(radius);
}

void CircleCollider::setRadius(float radius)
{
	drawCircle.setRadius(radius);
	drawCircle.setPosition(-radius, -radius);

	this->radius = radius;
}

void CircleCollider::debugDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(Locator::getSceneManager().debugShowHitboxes()) {
		states.transform *= getTransform();
		target.draw(drawCircle, states);
	}
}

float CircleCollider::getTransformedRadius() const
{
	sf::Vector2f scale = getScale();

	if (auto parent = parent_.lock()) {
		scale.x *= parent->getScale().x;
		scale.y *= parent->getScale().y;
	}

	return radius * ((scale.x + scale.y) / 2.f);
}

sf::Vector2f CircleCollider::getTransformedCenter() const
{
	sf::Transform transform;

	if (auto parent = parent_.lock()) {
		transform *= parent->getTransform();
	}

	transform *= getTransform();

	return transform.transformPoint(sf::Vector2f(0,0));
}

bool CircleCollider::isCollidingWith(const sf::Vector2f& point) const
{
	float distance = std::sqrt(vectorSquareLength(getPosition() - point));
	return distance < radius;
}

bool CircleCollider::isCollidingWith(const Collider& other) const
{
	return other.isCollidingWith(*this);
}

bool CircleCollider::isCollidingWith(const BoxCollider& box) const
{
	return box.isCollidingWith(*this);
}

bool CircleCollider::isCollidingWith(const CircleCollider& circle) const
{
	float distance = std::sqrt(vectorSquareLength(getTransformedCenter() - circle.getTransformedCenter()));
	return distance < getTransformedRadius() + circle.getTransformedRadius();
}
