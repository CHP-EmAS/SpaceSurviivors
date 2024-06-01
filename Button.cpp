#include "Button.h"
#include "Locator.h"

Button::Button()
{
	for (int i = 0; i < 4; i++) {
		corners[i].setTexture(Locator::getGraphicService().getTexture(GraphicService::UI_Button));
		edges[i].setTexture(Locator::getGraphicService().getTexture(GraphicService::UI_Button));
	}
	
	base.setTexture(Locator::getGraphicService().getTexture(GraphicService::UI_Button));
	base.setTextureRect(sf::IntRect(6, 6, 1, 1));

	corners[0].setTextureRect(sf::IntRect(0, 0, 6, 6));
	corners[1].setTextureRect(sf::IntRect(7, 0, 6, 6));
	corners[2].setTextureRect(sf::IntRect(7, 7, 6, 6));
	corners[3].setTextureRect(sf::IntRect(0, 7, 6, 6));

	edges[0].setTextureRect(sf::IntRect(6, 0, 1, 6));
	edges[1].setTextureRect(sf::IntRect(7, 6, 6, 1));
	edges[2].setTextureRect(sf::IntRect(6, 7, 1, 6));
	edges[3].setTextureRect(sf::IntRect(0, 6, 6, 1));

	setSize(sf::Vector2f(13, 13));
	mouseOver = true;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (int i = 0; i < 4; i++) {
		target.draw(corners[i], states);
		target.draw(edges[i], states);
	}

	target.draw(base, states);
	target.draw(text, states);

	if (Locator::getSceneManager().debugShowHitboxes()) {
		target.draw(collider, states);
	}
}

void Button::update()
{
	sf::Vector2f mousePosition = Locator::getSceneManager().getMousePosition();
	mousePosition = getInverseTransform().transformPoint(mousePosition);

	if (collider.isCollidingWith(mousePosition)) {
		if (!mouseOver) {
			setColor(sf::Color(255, 255, 255, 255));
			mouseOver = true;
		} 
	} else {
		if (mouseOver) {
			setColor(sf::Color(175, 175, 175, 255));
			mouseOver = false;
		}
	}
}

void Button::setSize(sf::Vector2f size)
{
	size.x = std::max(13.f, size.x);
	size.y = std::max(13.f, size.y);

	float scaleX = size.x - 12.f;
	float scaleY = size.y - 12.f;

	base.setScale(scaleX, scaleY);
	base.setPosition(6, 6);

	edges[0].setScale(scaleX, 1);
	edges[1].setScale(1, scaleY);
	edges[2].setScale(scaleX, 1);
	edges[3].setScale(1, scaleY);

	edges[0].setPosition(6, 0);
	edges[1].setPosition(6 + scaleX, 6);
	edges[2].setPosition(6, 6 + scaleY);
	edges[3].setPosition(0, 6);

	corners[0].setPosition(0, 0);
	corners[1].setPosition(6 + scaleX, 0);
	corners[2].setPosition(6 + scaleX, 6 + scaleY);
	corners[3].setPosition(0, 6 + scaleY);

	collider.setSize(size);
	this->size = size;

	setText(text);
}

void Button::setText(sf::Text newText)
{
	text = newText;
	
	sf::FloatRect textRect = text.getGlobalBounds();

	text.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
	text.setPosition(size.x / 2 - textRect.left, size.y / 2 - textRect.top);
}

bool Button::isHovered()
{
	return mouseOver;
}

void Button::setColor(sf::Color color)
{
	base.setColor(color);

	for (int i = 0; i < 4; i++) {
		corners[i].setColor(color);
		edges[i].setColor(color);
	}
}
