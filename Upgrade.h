#pragma once

#include "Button.h"
#include "DropShadowText.h"

class Upgrade : public sf::Drawable, public sf::Transformable
{
public:
	enum Rarity {
		COMMON,
		RARE,
		EPIC,
		LEGENDARY
	};

	enum Parameter {
		PlayerSpeed,
		PlayerShotsPerSeconds,
		PlayerDamage,
		ScoreMultiplier,
		Heal,
		MaxHealth,
		ExperienceMultiplier,
		Luck
	};

	struct Info {
		Parameter parameter;

		std::string parameterName;
		int charSize;

		float commonValue;
		float rareValue;
		float epicValue;
		float legendaryValue;
	};

	Upgrade();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update();

	bool isSelected();

	void setRarity(Rarity rarity);
	void setInfo(Info info, float currentValue);
	
	float getRarityValue();
	Info getInfo();
private:
	std::string convertFixedValue(float value);

	Button button;
	DropShadowText headerText;
	DropShadowText infoText;

	Rarity rarity;
	Info info;
};

