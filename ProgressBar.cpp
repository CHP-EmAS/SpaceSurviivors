#include "ProgressBar.h"
#include "Locator.h"

ProgressBar::ProgressBar()
{
	frame.setTexture(Locator::getGraphicService().getTexture(GraphicService::UI_LongPanel));
	
	barBeginn.setTexture(Locator::getGraphicService().getTexture(GraphicService::UI_BlueBar));
	barMiddle.setTexture(Locator::getGraphicService().getTexture(GraphicService::UI_BlueBar));
	barEnd.setTexture(Locator::getGraphicService().getTexture(GraphicService::UI_BlueBar));

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

	target.draw(barBeginn, states);
	target.draw(barMiddle, states);
	target.draw(barEnd, states);

	target.draw(frame, states);
}

void ProgressBar::setProgress(float progress)
{
	barMiddle.setScale(240 * progress, 1);
	barEnd.setPosition(barMiddle.getGlobalBounds().left + barMiddle.getGlobalBounds().width, 2);
}
