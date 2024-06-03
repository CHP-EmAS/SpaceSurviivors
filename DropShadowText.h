#pragma once

#include <SFML/Graphics.hpp>

class DropShadowText : public sf::Drawable, public sf::Transformable
{
public:
	DropShadowText();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setText(const sf::Text& style);
	void setColor(const sf::Color color);
	void setString(std::string string);
	void setShadowOffset(float offset);

	const sf::Text& getText();
	sf::Color getColor();
private:
	sf::Text text;
	sf::Text shadow;

	float offset;
};

