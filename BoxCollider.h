#pragma once

#include <SFML/Graphics.hpp>

#include "Collider.h"
#include "Component.h"


class BoxCollider : public Collider, public Component, public sf::Transformable
{
public:
	BoxCollider();
	BoxCollider(std::shared_ptr<GameObject> parent, float width, float height);
	BoxCollider(std::shared_ptr<GameObject> parent, sf::Vector2f size);

	void setSize(float width, float height);
	void setSize(sf::Vector2f size);

	void debugDraw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void getTransformedVertices(sf::Vector2f vertices[4]) const;

private:
	sf::FloatRect hitbox;
	sf::RectangleShape drawBox;

	sf::FloatRect getAABB() override;

	bool isCollidingWith(const sf::Vector2f& point) const override;
	bool isCollidingWith(const Collider& other) const override;
	bool isCollidingWith(const BoxCollider& box) const override;
	bool isCollidingWith(const CircleCollider& circle) const override;
};

