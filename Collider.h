#pragma once

#include <SFML/Graphics.hpp>

class GameObject;
class Collider : public sf::Transformable, public sf::Drawable
{
public:
	Collider();
	Collider(GameObject* parent, float width, float height);
	Collider(GameObject* parent, sf::Vector2f size);
	
	void setSize(float width, float height);
	void setSize(sf::Vector2f size);

	bool isCollidingWith(Collider* other);
	bool isCollidingWith(sf::Vector2f point);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void getTransformedVertices(sf::Vector2f vertices[4]);
	
private:
	GameObject* bindObject;
	sf::FloatRect hitbox;

	sf::RectangleShape drawBox;
};

