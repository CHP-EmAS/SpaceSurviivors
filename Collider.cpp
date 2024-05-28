#include "Collider.h"
#include "GameObject.h"
#include "VectorExtension.h"

Collider::Collider() : 
    Collider(nullptr, sf::Vector2f(0, 0)) {}

Collider::Collider(GameObject* parent, float width, float height) : 
    Collider(parent, sf::Vector2f(width, height)) {}

Collider::Collider(GameObject* parent, sf::Vector2f size)
{
	bindObject = parent;

	hitbox.top = 0;
	hitbox.left = 0;
    hitbox.width = size.x;
	hitbox.height = size.y;
	
	drawBox.setFillColor(sf::Color(255, 0, 255, 120));
	drawBox.setOutlineColor(sf::Color::Magenta);
	drawBox.setOutlineThickness(1);
	drawBox.setSize(size);
}

void Collider::setSize(float width, float height)
{
    setSize(sf::Vector2f(width, height));
}

void Collider::setSize(sf::Vector2f size)
{
    hitbox.width = size.x;
	hitbox.height = size.y;
	
	drawBox.setSize(size);
}

bool Collider::isCollidingWith(Collider* other)
{
    if (hitbox.width == 0 || hitbox.height == 0) {
        return false;
    }

    sf::Vector2f thisPoints[4];
    sf::Vector2f otherPoints[4];

    getTransformedVertices(thisPoints);
    other->getTransformedVertices(otherPoints);

    sf::Vector2f axes[4] = {
        VectorExtension::normalize(thisPoints[1] - thisPoints[0]),
        VectorExtension::normalize(thisPoints[3] - thisPoints[0]),
        VectorExtension::normalize(otherPoints[1] - otherPoints[0]),
        VectorExtension::normalize(otherPoints[3] - otherPoints[0])
    };

    // Project points onto the axis and check for separation
    for (const sf::Vector2f& axis : axes)
    {
        float thisMin = VectorExtension::dotP(thisPoints[0], axis);
        float thisMax = thisMin;
        float otherMin = VectorExtension::dotP(otherPoints[0], axis);
        float otherMax = otherMin;

        for (int i = 1; i < 4; ++i)
        {
            float thisProjection = VectorExtension::dotP(thisPoints[i], axis);
            thisMin = std::min(thisMin, thisProjection);
            thisMax = std::max(thisMax, thisProjection);

            float otherProjection = VectorExtension::dotP(otherPoints[i], axis);
            otherMin = std::min(otherMin, otherProjection);
            otherMax = std::max(otherMax, otherProjection);
        }

        // Check for separation
        if (thisMax < otherMin || otherMax < thisMin)
        {
            return false;
        }
    }

    return true;
}

bool Collider::isCollidingWith(sf::Vector2f point)
{
    sf::Transform inverse = getInverseTransform();

    if (bindObject != nullptr) {
        inverse *= bindObject->getInverseTransform();
    }

	return hitbox.contains(inverse.transformPoint(point));
}

void Collider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(drawBox, states);
}

void Collider::getTransformedVertices(sf::Vector2f vertices[4])
{
    sf::Transform transform;

    if (bindObject != nullptr) {
        transform *= bindObject->getTransform();
    }

    transform *= getTransform();

    vertices[0] = transform.transformPoint(sf::Vector2f(0, 0));
    vertices[1] = transform.transformPoint(sf::Vector2f(hitbox.width, 0));
    vertices[2] = transform.transformPoint(sf::Vector2f(hitbox.width, hitbox.height));
    vertices[3] = transform.transformPoint(sf::Vector2f(0, hitbox.height));
}
