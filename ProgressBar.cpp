#include "ProgressBar.h"
#include "Locator.h"

ProgressBar::ProgressBar()
{
	setLength(100);
	progress = 0;
	
	barBeginn.setTexture(Locator::get<GraphicService>()->getTexture(GraphicService::UI_BlueBar));
	barMiddle.setTexture(Locator::get<GraphicService>()->getTexture(GraphicService::UI_BlueBar));
	barEnd.setTexture(Locator::get<GraphicService>()->getTexture(GraphicService::UI_BlueBar));

	barBeginn.setTextureRect(sf::IntRect(0, 0, 6, 26));
	barMiddle.setTextureRect(sf::IntRect(6, 0, 1, 26));
	barEnd.setTextureRect(sf::IntRect(7, 0, 6, 26));

	barMiddle.setScale(0, 1);

	barBeginn.setPosition(2, 2);
	barMiddle.setPosition(barBeginn.getGlobalBounds().left + barBeginn.getGlobalBounds().width, 2);
	barEnd.setPosition(barMiddle.getGlobalBounds().left + barMiddle.getGlobalBounds().width, 2);
}

void ProgressBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	if (progress > 0.f) {
		target.draw(barBeginn, states);
		target.draw(barMiddle, states);
		target.draw(barEnd, states);
	}

	target.draw(frame, states);
}

void ProgressBar::setTexture(const sf::Texture& barTexture)
{
	barBeginn.setTexture(barTexture);
	barMiddle.setTexture(barTexture);
	barEnd.setTexture(barTexture);
}

void ProgressBar::setLength(float length)
{
	frame.setSize(sf::Vector2f(length, 30));
}

void ProgressBar::setProgress(float progress)
{
	this->progress = progress;
	barMiddle.setScale((frame.getSize().x - 14) * progress, 1);
	barEnd.setPosition(barMiddle.getGlobalBounds().left + barMiddle.getGlobalBounds().width, 2);
}
