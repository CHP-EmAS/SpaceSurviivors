#include "CircleCollider.h"

#include "Locator.h"
#include "BoxCollider.h"
#include "VectorExtension.h"


CircleCollider::CircleCollider() :
	CircleCollider(nullptr, 0) {}

CircleCollider::CircleCollider(std::shared_ptr<GameObject> parent, float radius) : Collider(parent)
{
	debugCircle.setFillColor(sf::Color(255, 255, 0, 130));
	setRadius(radius);
}

void CircleCollider::setRadius(float radius)
{
	debugCircle.setRadius(radius);
	debugCircle.setPosition(-radius, -radius);

	this->radius = radius;
}

float CircleCollider::getTransformedRadius() const
{
	if (dirty) {
		calculateParameters();
	}

	return transformedRadius;
}

sf::Vector2f CircleCollider::getTransformedCenter() const
{
	if (dirty) {
		calculateParameters();
	}

	return transformedCenter;
}

bool CircleCollider::isCollidingWith(const sf::Vector2f& point) const
{
	float distance = std::sqrt(vectorSquareLength(getTransformedCenter() - point));
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

void CircleCollider::calculateParameters() const
{
	sf::Transform transform;
	sf::Vector2f scale = getScale();

	if (auto parent = _parent.lock()) {
		transform = parent->getTransform();
		scale.x *= parent->getScale().x;
		scale.y *= parent->getScale().y;
	}

	transform *= getTransform();

	transformedCenter = transform.transformPoint(sf::Vector2f());
	transformedRadius = radius * ((scale.x + scale.y) / 2.f);

	float diameter = transformedRadius * 2.f;
	sf::Vector2f position = transformedCenter - sf::Vector2f(transformedRadius, transformedRadius);
	
	aabb.left = position.x;
	aabb.top = position.y;
	aabb.height = diameter;
	aabb.width = diameter;

	//flag
	dirty = false;
}

void CircleCollider::onDebugDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (Locator::get<SceneManager>()->debugShowHitboxes()) {
		states.transform *= getTransform();
		target.draw(debugCircle, states);

		debugBoundingBox.setPosition(aabb.getPosition());
		debugBoundingBox.setSize(aabb.getSize());

		sf::CircleShape dot(2.f);
		dot.setPosition(getTransformedCenter());
		target.draw(dot);

		target.draw(debugBoundingBox);
	}
}
