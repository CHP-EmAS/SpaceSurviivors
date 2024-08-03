#include <algorithm>

#include "ParallaxBackground.h"
#include "Locator.h"

ParallaxBackground::ParallaxBackground() : maxOffset1(50), maxOffset2(100), maxOffset3(200)
{
	const sf::Vector2f scale(0.5, 0.5);

	const int size0 = float(WORLD_SIZE) / scale.x;
	const int size1 = (float(WORLD_SIZE) + maxOffset1) / scale.x;
	const int size2 = (float(WORLD_SIZE) + maxOffset2) / scale.x;
	const int size3 = (float(WORLD_SIZE) + maxOffset3) / scale.x;

	background0.setTexture(Locator::get<GraphicService>()->getTexture(GraphicService::Background_0));
	background0.setTextureRect(sf::IntRect(0, 0, size0, size0));
	background0.setScale(scale);

	background1.setTexture(Locator::get<GraphicService>()->getTexture(GraphicService::Background_1));
	background1.setTextureRect(sf::IntRect(0, 0, size1, size1));
	background1.setScale(scale);
	
	background2.setTexture(Locator::get<GraphicService>()->getTexture(GraphicService::Background_2));
	background2.setTextureRect(sf::IntRect(0, 0, size2, size2));
	background2.setScale(scale);
	
	background3.setTexture(Locator::get<GraphicService>()->getTexture(GraphicService::Background_3));
	background3.setTextureRect(sf::IntRect(0, 0, size3, size3));
	background3.setScale(scale);
}

void ParallaxBackground::update(const sf::Vector2f referencePosition)
{
	sf::Vector2f relativePosition = sf::Vector2f(referencePosition.x / WORLD_SIZE, referencePosition.y / WORLD_SIZE);

	relativePosition.x = std::clamp(relativePosition.x, 0.f, 1.f);
	relativePosition.y = std::clamp(relativePosition.y, 0.f, 1.f);

	background1.setPosition(relativePosition * -maxOffset1);
	background2.setPosition(relativePosition * -maxOffset2);
	background3.setPosition(relativePosition * -maxOffset3);
}

void ParallaxBackground::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background0, states);
	target.draw(background1, states);
	target.draw(background2, states);
	target.draw(background3, states);
}
