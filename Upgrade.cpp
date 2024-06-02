#include <sstream>
#include <iomanip>

#include "Upgrade.h"
#include "Locator.h"

Upgrade::Upgrade()
{
	button.setSize(sf::Vector2f(166.66, 200));
	headerText.setPosition(166.66 / 2.f, 30);
	headerText.setShadowOffset(2);

	infoText.setPosition(166.66 / 2.f, 70);
	infoText.setShadowOffset(2);
}

void Upgrade::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(button, states);
	target.draw(headerText, states);
	target.draw(infoText, states);
}

void Upgrade::update()
{
	button.update(getTransform());
}

bool Upgrade::isSelected()
{
	return button.isHovered();
}

void Upgrade::setRarity(Rarity rarity)
{
	this->rarity = rarity;

	switch (rarity) {
	case COMMON:
		button.setColor(sf::Color::Cyan);
		break;
	case RARE:
		button.setColor(sf::Color::Yellow);
		break;
	case EPIC:
		button.setColor(sf::Color::Magenta);
		break;
	case LEGENDARY:
		button.setColor(sf::Color::Red);
		break;
	}
}

void Upgrade::setInfo(UpgradeInfo info)
{
	this->info = info;

	sf::Text text = sf::Text(info.parameterName, Locator::getGraphicService().getFont(GraphicService::Pixel), info.charSize);
	headerText.setText(text);
	headerText.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);

	std::stringstream stream;
	stream << std::fixed << std::setprecision(1);

	switch (rarity) {
	case COMMON:
		stream << info.commonValue;
		break;
	case RARE:
		stream << info.rareValue;
		break;
	case EPIC:
		stream << info.epicValue;
		break;
	case LEGENDARY:
		stream << info.legendaryValue;
		break;
	}

	std::string infoStr = stream.str();
	if (infoStr[0] != '-') {
		infoStr = "+ " + infoStr;
	}

	text = sf::Text(infoStr, Locator::getGraphicService().getFont(GraphicService::Pixel), 18);
	button.setText(text);

	//infoText.setText(text);
	//infoText.setOrigin(text.getLocalBounds().width / 2, 0);
}
