#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "Collider.h"
#include "Component.h"


class BoxCollider : public Collider
{
public:
	BoxCollider();
	BoxCollider(std::shared_ptr<GameObject> parent, float width, float height);
	BoxCollider(std::shared_ptr<GameObject> parent, sf::Vector2f size);

	void setSize(float width, float height);
	void setSize(sf::Vector2f size);

	std::array<sf::Vector2f, 4> getTransformedVertices() const;

	bool isCollidingWith(const sf::Vector2f& point) const override;
	bool isCollidingWith(const Collider& other) const override;
	bool isCollidingWith(const BoxCollider& box) const override;
	bool isCollidingWith(const CircleCollider& circle) const override;

	void onDebugDraw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::FloatRect hitbox;

	mutable std::array<sf::Vector2f, 4> vertices;
	mutable sf::RectangleShape debugHitbox;

	void calculateParameters() const override;
};

