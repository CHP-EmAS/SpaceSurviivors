#pragma once

#include "SFML/Graphics.hpp"

class BoxCollider;
class CircleCollider;

class Collider
{
public:
    virtual void debugDraw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

    virtual bool isCollidingWith(const sf::Vector2f& point) const = 0;

    virtual bool isCollidingWith(const Collider& other) const = 0;
    virtual bool isCollidingWith(const BoxCollider& box) const = 0;
    virtual bool isCollidingWith(const CircleCollider& circle) const = 0;
};

