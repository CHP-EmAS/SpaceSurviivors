#include "Button.h"
#include "Locator.h"

Button::Button()
{
	mouseOver = true;
	enabled = true;
	color = sf::Color(180, 220, 250);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(frame, states);
	target.draw(text, states);

	if (Locator::getSceneManager().debugShowHitboxes()) {
		target.draw(collider, states);
	}
}

void Button::update(const sf::Transform& parentTransform)
{
	if (!enabled)
		return;

	sf::Vector2f mousePosition = Locator::getSceneManager().getMousePosition();
	mousePosition = parentTransform.getInverse().transformPoint(mousePosition);
	mousePosition = getInverseTransform().transformPoint(mousePosition);

	if (collider.isCollidingWith(mousePosition)) {
		if (!mouseOver) {
			frame.setColor(color);
			text.setShadowOffset(1);
			mouseOver = true;
		} 
	} else {
		if (mouseOver) {
			frame.setColor(color - sf::Color(80, 80, 80, 0));
			text.setShadowOffset(3);
			mouseOver = false;
		}
	}
}

void Button::setSize(sf::Vector2f size)
{
	frame.setSize(size);
	collider.setSize(size);
	
	setText(text.getText());
}

void Button::setText(sf::Text newText)
{
	text.setText(newText);
	
	sf::FloatRect textRect = newText.getGlobalBounds();
	sf::Vector2f size = frame.getSize();

	text.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
	text.setPosition(size.x / 2 - textRect.left, size.y / 2 - textRect.top);
}

void Button::setColor(sf::Color newColor)
{
	color = newColor;

	if (mouseOver) {
		frame.setColor(color);
	} else {
		frame.setColor(color - sf::Color(80, 80, 80, 0));
	}
}

void Button::setEnabled(bool enabled)
{
	this->enabled = enabled;
	
	if (enabled) {
		frame.setColor(color - sf::Color(80, 80, 80, 0));
	} else {
		frame.setColor(sf::Color(100, 100, 100, color.a));
		mouseOver = false;
	}
}

bool Button::isHovered()
{
	return mouseOver;
}

bool Button::isEnabled()
{
	return enabled;
}
