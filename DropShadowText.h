#pragma once

#include <SFML/Graphics.hpp>

class DropShadowText : public sf::Drawable, public sf::Transformable
{
public:
	DropShadowText();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setText(const sf::Text& style);
	void setString(std::string string);
	void setShadowOffset(float offset);

	const sf::Text& getText();
private:
	sf::Text text;
	sf::Text shadow;

	float offset;
};

