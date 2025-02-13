#include <sstream>
#include <iomanip>

#include "Upgrade.h"
#include "Locator.h"

Upgrade::Upgrade() : rarity(COMMON)
{
	button.setSize(sf::Vector2f(166.66, 200));
	headerText.setPosition(166.66 / 2.f, 30);
	headerText.setShadowOffset(3);
	headerText.setFont(Locator::get<GraphicService>()->getFont(GraphicService::Pixel));

	infoText.setPosition(166.66 / 2.f, 180);
	infoText.setFont(Locator::get<GraphicService>()->getFont(GraphicService::Pixel));
	infoText.setFontSize(12);
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

	if (!button.isHovered()) {
		headerText.setShadowOffset(3);
		infoText.setShadowOffset(2);
	} else {
		headerText.setShadowOffset(1);
		infoText.setShadowOffset(1);
	}
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
		button.setColor(sf::Color::Green);
		headerText.setColor(sf::Color::Green);
		break;
	case RARE:
		button.setColor(sf::Color::Cyan);
		headerText.setColor(sf::Color::Cyan);
		break;
	case EPIC:
		button.setColor(sf::Color::Magenta);
		headerText.setColor(sf::Color(220, 0, 255));
		break;
	case LEGENDARY:
		button.setColor(sf::Color(255, 200, 0));
		headerText.setColor(sf::Color(255, 200, 0));
		break;
	}
}

void Upgrade::setInfo(Info info, float current)
{
	this->info = info;

	//Header
	headerText.setString(info.parameterName);
	headerText.setFontSize(info.charSize);
	headerText.setOrigin(headerText.getLocalBounds().width / 2.f, headerText.getLocalBounds().height / 2.f);

	//Value to Add
	std::string upgradeValueStr = convertFixedValue(getRarityValue());
	button.setText(sf::Text("+ " + upgradeValueStr, Locator::get<GraphicService>()->getFont(GraphicService::Pixel), 20));

	//Current
	std::string currentValueStr = convertFixedValue(current);
	infoText.setString("Current: " + currentValueStr);
	infoText.setOrigin(infoText.getLocalBounds().width / 2.f, infoText.getLocalBounds().height);
}

float Upgrade::getRarityValue() const
{
	switch (rarity) {
	case COMMON:
		return info.commonValue;
	case RARE:
		return info.rareValue;
	case EPIC:
		return info.epicValue;
	case LEGENDARY:
		return info.legendaryValue;
	default:
		return 0.f;
	}
}

Upgrade::Info Upgrade::getInfo() const
{
	return info;
}

std::string Upgrade::convertFixedValue(float value) const
{
	std::stringstream sstream;
	sstream << std::fixed;

	if (value == (int)value) {
		sstream << std::setprecision(0);
	} else {
		sstream << std::setprecision(1);
	}

	sstream << value;
	return sstream.str();
}
