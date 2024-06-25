#pragma once

#include <SFML/Graphics.hpp>
#include "Frame.h"

class TextInput : public sf::Drawable, public sf::Transformable
{
public:
	TextInput();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void checkEvents(sf::Event event);

	void updateText();
	void clear();

	void setSize(sf::Vector2f size);
	void setFontSize(int size);

	bool isEmpty();

	std::string getText();
	sf::Vector2f getSize();

private:
	Frame frame;
	sf::Text text;
};

