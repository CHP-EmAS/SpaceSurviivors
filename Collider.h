#pragma once

#include <iostream>

#include "SFML/Graphics.hpp"
#include "Component.h"

class BoxCollider;
class CircleCollider;

class Collider : public Component, public sf::Transformable
{
public:
    Collider() : Collider(nullptr) {};
    Collider(std::shared_ptr<GameObject> parent) : Component(parent), dirty(true) {
        debugBoundingBox.setFillColor(sf::Color::Transparent);
        debugBoundingBox.setOutlineColor(sf::Color::Magenta);
        debugBoundingBox.setOutlineThickness(-1);
    };

    virtual void onUpdate(const sf::Time& deltaTime) override { dirty = true; };
	virtual void onDebugDraw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

    virtual bool isCollidingWith(const sf::Vector2f& point) const = 0;

    virtual bool isCollidingWith(const Collider& other) const = 0;
    virtual bool isCollidingWith(const BoxCollider& box) const = 0;
    virtual bool isCollidingWith(const CircleCollider& circle) const = 0;

    virtual const sf::FloatRect& getContainingAABB() {
        if (dirty) {
            calculateParameters();
        }
            
        return aabb;
    };

protected:
    mutable sf::FloatRect aabb;
    mutable bool dirty;

    mutable sf::RectangleShape debugBoundingBox;

    virtual void calculateParameters() const = 0;
};

