#pragma once

#include "Collider.h"
#include "GameObject.h"

class CircleCollider : public Collider
{
public:
	CircleCollider();
	CircleCollider(std::shared_ptr<GameObject> parent, float radius);

	void setRadius(float radius);
	
	float getTransformedRadius() const;
	sf::Vector2f getTransformedCenter() const;

	bool isCollidingWith(const sf::Vector2f& point) const override;
	bool isCollidingWith(const Collider& other) const override;
	bool isCollidingWith(const BoxCollider& box) const override;
	bool isCollidingWith(const CircleCollider& circle) const override;

	void onDebugDraw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	float radius;

	mutable float transformedRadius;
	mutable sf::Vector2f transformedCenter;

	sf::CircleShape debugCircle;

	void calculateParameters() const override;
};

