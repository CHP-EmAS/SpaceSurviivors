#include "DropShadowText.h"

#include "iostream"
#include "Locator.h"

DropShadowText::DropShadowText()
{
	setShadowOffset(3);
	setShadowColor(sf::Color::Black);
}

void DropShadowText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(shadow, states);
	target.draw(text, states);
}

void DropShadowText::setText(const sf::Text& style)
{
	setColor(style.getFillColor());
	setFont(*style.getFont());
	setFontSize(style.getCharacterSize());
	setString(style.getString());
	setLetterSpacing(style.getLetterSpacing());
}

void DropShadowText::setColor(const sf::Color color)
{
	text.setFillColor(color);
}

void DropShadowText::setShadowColor(const sf::Color color)
{
	shadowColor = color;
	shadow.setFillColor(color);
}

void DropShadowText::setFont(const sf::Font& font)
{
	text.setFont(font);
	shadow.setFont(font);
}

void DropShadowText::setFontSize(unsigned int fontSize)
{
	text.setCharacterSize(fontSize);
	shadow.setCharacterSize(fontSize);
}

void DropShadowText::setString(std::string string)
{
	text.setString(string);
	shadow.setString(string);
}

void DropShadowText::setLetterSpacing(float spacing)
{
	text.setLetterSpacing(spacing);
	shadow.setLetterSpacing(spacing);
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

sf::FloatRect DropShadowText::getLocalBounds()
{
	sf::FloatRect textRect = text.getLocalBounds();

	textRect.width += textRect.left;
	textRect.height += textRect.top;
	//textRect.width += offset;
	//textRect.height += offset;
	textRect.left = 0;
	textRect.top = 0;

	return textRect;
}

sf::Color DropShadowText::getColor()
{
	return text.getFillColor();
}
