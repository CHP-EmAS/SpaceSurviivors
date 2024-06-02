#include "Frame.h"

#include "Locator.h"

Frame::Frame()
{
	for (int i = 0; i < 4; i++) {
		corners[i].setTexture(Locator::getGraphicService().getTexture(GraphicService::UI_Frame));
		edges[i].setTexture(Locator::getGraphicService().getTexture(GraphicService::UI_Frame));
	}

	base.setTexture(Locator::getGraphicService().getTexture(GraphicService::UI_Frame));
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
}

void Frame::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (int i = 0; i < 4; i++) {
		target.draw(corners[i], states);
		target.draw(edges[i], states);
	}

	target.draw(base, states);
}

void Frame::setSize(sf::Vector2f size)
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
	
	this->size = size;
}

void Frame::setColor(sf::Color newColor)
{
	base.setColor(newColor);

	for (int i = 0; i < 4; i++) {
		corners[i].setColor(newColor);
		edges[i].setColor(newColor);
	}
}

sf::Vector2f Frame::getSize()
{
	return size;
}
