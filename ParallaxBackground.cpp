#include <algorithm>

#include "ParallaxBackground.h"
#include "Locator.h"

ParallaxBackground::ParallaxBackground()
{
	background0.setSize(sf::Vector2f(WINDOW_SIZE, WINDOW_SIZE));
	background0.setTexture(&Locator::getGraphicService().getTexture(GraphicService::Background_0));

	maxOffset1 = 50;
	background1.setSize(sf::Vector2f(WINDOW_SIZE + maxOffset1, WINDOW_SIZE + maxOffset1));
	background1.setTexture(&Locator::getGraphicService().getTexture(GraphicService::Background_1));

	maxOffset2 = 100;
	background2.setSize(sf::Vector2f(WINDOW_SIZE + maxOffset2, WINDOW_SIZE + maxOffset2));
	background2.setTexture(&Locator::getGraphicService().getTexture(GraphicService::Background_2));

	maxOffset3 = 200;
	background3.setSize(sf::Vector2f(WINDOW_SIZE + maxOffset3, WINDOW_SIZE + maxOffset3));
	background3.setTexture(&Locator::getGraphicService().getTexture(GraphicService::Background_3));
}

void ParallaxBackground::update(const sf::Vector2f referencePosition)
{
	sf::Vector2f relativePosition = sf::Vector2f(referencePosition.x / WINDOW_SIZE, referencePosition.y / WINDOW_SIZE);

	relativePosition.x = std::clamp(relativePosition.x, 0.f, 1.f);
	relativePosition.y = std::clamp(relativePosition.y, 0.f, 1.f);

	background1.setPosition(relativePosition * -maxOffset1);
	background2.setPosition(relativePosition * -maxOffset2);
	background3.setPosition(relativePosition * -maxOffset3);
}

void ParallaxBackground::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background0);
	target.draw(background1);
	target.draw(background2);
	target.draw(background3);
}
