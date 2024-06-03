#include "DropShadowText.h"

#include "iostream"

DropShadowText::DropShadowText()
{
	offset = 3;
}

void DropShadowText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(shadow, states);
	target.draw(text, states);
}

void DropShadowText::setText(const sf::Text& style)
{
	text = sf::Text(style);
	text.setPosition(0,0);
	text.setOrigin(0,0);
	text.setRotation(0);
	text.setScale(1,1);

	shadow = sf::Text(text);
	shadow.setFillColor(sf::Color::Black);
	shadow.setPosition(offset, offset);
}

void DropShadowText::setColor(const sf::Color color)
{
	text.setFillColor(color);
}

void DropShadowText::setString(std::string string)
{
	text.setString(string);
	shadow.setString(string);
}

void DropShadowText::setShadowOffset(float offset)
{
	this->offset = offset;
	shadow.setPosition(offset, offset);
}

const sf::Text& DropShadowText::getText()
{
	return text;
}

sf::Color DropShadowText::getColor()
{
	return text.getFillColor();
}
