#pragma once

#include <SFML/Graphics.hpp>
#include "BoxCollider.h"
#include "Frame.h"
#include "DropShadowText.h"

class Button : public sf::Drawable, public sf::Transformable
{
public:
	Button();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(const sf::Transform& parentTransform = sf::Transform::Identity);

	void setSize(sf::Vector2f size);
	void setText(sf::Text newText);
	void setColor(sf::Color newColor);
	void setEnabled(bool enabled);

	bool isHovered();
	bool isEnabled();

private:
	Frame frame;
	DropShadowText text;

	BoxCollider collider;

	bool mouseOver;
	bool enabled;

	sf::Color color;
};

