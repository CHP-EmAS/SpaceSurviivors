#include "BoxCollider.h"
#include "CircleCollider.h"

#include "GameObject.h"
#include "Locator.h"
#include "VectorExtension.h"

BoxCollider::BoxCollider() :
    BoxCollider(nullptr, sf::Vector2f(0,0)) {}

BoxCollider::BoxCollider(std::shared_ptr<GameObject> parent, float width, float height) :
    BoxCollider(parent, sf::Vector2f(width, height)){}

BoxCollider::BoxCollider(std::shared_ptr<GameObject> parent, sf::Vector2f size) : Component(parent)
{
    drawBox.setFillColor(sf::Color(255, 255, 0, 130));
    setSize(size);
}

void BoxCollider::setSize(float width, float height)
{
    setSize(sf::Vector2f(width, height));
}

void BoxCollider::setSize(sf::Vector2f size)
{
    hitbox.left = -size.x / 2.f;
    hitbox.top = -size.y / 2.f;
    hitbox.width = size.x;
    hitbox.height = size.y;

    drawBox.setPosition(hitbox.getPosition());
    drawBox.setSize(hitbox.getSize());
}

void BoxCollider::debugDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (Locator::getSceneManager().debugShowHitboxes()) {
        states.transform *= getTransform();
        target.draw(drawBox, states);
    }
}

void BoxCollider::getTransformedVertices(sf::Vector2f vertices[4]) const
{
    sf::Transform transform;

    if (auto parent = parent_.lock()) {
        transform *= parent->getTransform();
    }

    transform *= getTransform();

    float halfWidth = hitbox.width / 2.f;
    float halfHeight = hitbox.height / 2.f;

    vertices[0] = transform.transformPoint(sf::Vector2f(-halfWidth, -halfHeight));
    vertices[1] = transform.transformPoint(sf::Vector2f(halfWidth, -halfHeight));
    vertices[2] = transform.transformPoint(sf::Vector2f(halfWidth, halfHeight));
    vertices[3] = transform.transformPoint(sf::Vector2f(-halfWidth, halfHeight));
}

bool BoxCollider::isCollidingWith(const sf::Vector2f& point) const
{
    sf::Transform inverse = getInverseTransform();

    if (auto parent = parent_.lock()) {
        inverse *= parent->getInverseTransform();
    }

    return hitbox.contains(inverse.transformPoint(point));
}

bool BoxCollider::isCollidingWith(const Collider& other) const
{
    return other.isCollidingWith(*this);
}

bool BoxCollider::isCollidingWith(const BoxCollider& box) const
{
    if (hitbox.width == 0 || hitbox.height == 0) {
        return false;
    }

    sf::Vector2f thisPoints[4];
    sf::Vector2f otherPoints[4];

    getTransformedVertices(thisPoints);
    box.getTransformedVertices(otherPoints);

    sf::Vector2f axes[4] = {
        normalize(thisPoints[1] - thisPoints[0]),
        normalize(thisPoints[3] - thisPoints[0]),
        normalize(otherPoints[1] - otherPoints[0]),
        normalize(otherPoints[3] - otherPoints[0])
    };

    for (const sf::Vector2f& axis : axes)
    {
        float thisMin = dotP(thisPoints[0], axis);
        float thisMax = thisMin;
        float otherMin = dotP(otherPoints[0], axis);
        float otherMax = otherMin;

        for (int i = 1; i < 4; ++i)
        {
            float thisProjection = dotP(thisPoints[i], axis);
            thisMin = std::min(thisMin, thisProjection);
            thisMax = std::max(thisMax, thisProjection);

            float otherProjection = dotP(otherPoints[i], axis);
            otherMin = std::min(otherMin, otherProjection);
            otherMax = std::max(otherMax, otherProjection);
        }

        if (thisMax < otherMin || otherMax < thisMin)
        {
            return false;
        }
    }

    return true;
}

bool BoxCollider::isCollidingWith(const CircleCollider& circle) const
{
    sf::Transform inverse = getInverseTransform();

    if (auto parent = parent_.lock()) {
        inverse *= parent->getInverseTransform();
    }

    const sf::Vector2f circleCenter = inverse.transformPoint(circle.getTransformedCenter());
    const float circleRadius = circle.getTransformedRadius();

    sf::Vector2f dist(circleCenter - hitbox.getPosition() - hitbox.getSize() / 2.f);
    dist.x = std::abs(dist.x);
    dist.y = std::abs(dist.y);

    if (dist.x > hitbox.width / 2.f + circleRadius) {
        return false;
    }
    if (dist.y > hitbox.height / 2.f + circleRadius) {
        return false;
    }

    if (dist.x <= hitbox.width / 2.f) {
        return true;
    }
    if (dist.y <= hitbox.height / 2.f) {
        return true;
    }

    const sf::Vector2f delta(dist - hitbox.getSize() / 2.f);
    return vectorSquareLength(delta) <= circleRadius * circleRadius;
}

sf::FloatRect BoxCollider::getAABB()
{
    float rotationDeg = getRotation();

    if (auto parent = parent_.lock()) {
        rotationDeg += parent->getRotation();
    }

    float rad = rotationDeg * (M_PI / 180.0f);

    float cosTheta = std::cos(rad);
    float sinTheta = std::sin(rad);

    float width = std::abs(hitbox.width * cosTheta) + std::abs(hitbox.height * sinTheta);
    float height = std::abs(hitbox.width * sinTheta) + std::abs(hitbox.height * cosTheta);
}
