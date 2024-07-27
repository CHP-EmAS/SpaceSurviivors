#pragma once

#include "Collider.h"
#include "Component.h"

#include "GameObject.h"

class CircleCollider : public Collider, public Component, public sf::Transformable
{
public:
	CircleCollider();
	CircleCollider(std::shared_ptr<GameObject>, float radius);

	void setRadius(float radius);
	
	void debugDraw(sf::RenderTarget& target, sf::RenderStates states) const override;

	float getTransformedRadius() const;
	sf::Vector2f getTransformedCenter() const;

	bool isCollidingWith(const sf::Vector2f& point) const override;
	bool isCollidingWith(const Collider& other) const override;
	bool isCollidingWith(const BoxCollider& box) const override;
	bool isCollidingWith(const CircleCollider& circle) const override;

private:
	float radius;
	sf::CircleShape drawCircle;

};

