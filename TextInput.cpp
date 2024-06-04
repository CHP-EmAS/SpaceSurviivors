#include "TextInput.h"
#include "Locator.h"

TextInput::TextInput()
{
	text = sf::Text("", Locator::getGraphicService().getFont(GraphicService::Pixel), 23);
	setSize(sf::Vector2f(300,45));
}

void TextInput::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(frame, states);
	target.draw(text, states);
}

void TextInput::checkEvents(sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::TextEntered:
		if (event.text.unicode >= 32 && event.text.unicode <= 122 || event.text.unicode == 124 || event.text.unicode == 126)
		{
			if (text.getString().getSize() < 14)
				text.setString(text.getString() + (char)event.text.unicode);
		}
		else if (event.text.unicode == 8)
		{
			if (text.getString().getSize() > 0)
				text.setString(text.getString().substring(0, text.getString().getSize() - 1));
		}
		
		updateText();

		break;
	}
}

void TextInput::updateText()
{
	sf::Vector2f size = frame.getSize();
	sf::FloatRect textRect = text.getLocalBounds();

	text.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
	text.setPosition(size.x / 2 - textRect.left, size.y / 2 - textRect.top);
}

void TextInput::clear()
{
	text.setString("");
	updateText();
}

void TextInput::setSize(sf::Vector2f size)
{
	frame.setSize(size);
	updateText();
}

void TextInput::setFontSize(int size)
{
	text.setCharacterSize(size);
}

std::string TextInput::getText()
{
	return text.getString();
}

sf::Vector2f TextInput::getSize()
{
	return frame.getSize();
}
