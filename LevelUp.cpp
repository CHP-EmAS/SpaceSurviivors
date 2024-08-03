#include "LevelUp.h"
#include "Locator.h"
#include <array>

const int NUM_UPGRADES = 3;
const std::array<int, 4> DEFAULT_PROBABILITIES = { 80, 15, 5, 0 };

LevelUpScene::LevelUpScene() : Scene(Level_UP)
{
	// Initialize upgrade positions and scales
	for (int i = 0; i < NUM_UPGRADES; ++i) {
		upgrade[i].setScale(1.5f, 1.5f);
		upgrade[i].setPosition((250 * i) + (62.5f * (i + 1)), 400);
	}

	// Initialize level up text
	levelUpText.setFont(Locator::get<GraphicService>()->getFont(GraphicService::Pixel));
	levelUpText.setFontSize(55);
	levelUpText.setString("Level Up!");
	levelUpText.setColor(sf::Color(255, 223, 0));
	levelUpText.setOrigin(levelUpText.getLocalBounds().width / 2, 0);
	levelUpText.setPosition(WINDOW_SIZE / 2, 200);
	levelUpText.setShadowOffset(5);

	// Initialize info text
	infoText.setFont(Locator::get<GraphicService>()->getFont(GraphicService::Pixel));
	infoText.setFontSize(24);
	infoText.setString("Choose one of the upgrades");
	infoText.setOrigin(infoText.getLocalBounds().width / 2, 0);
	infoText.setPosition(WINDOW_SIZE / 2, 280);
	infoText.setShadowOffset(3);

	rarityFrame.setPosition(500, 885);

	InitUpgradeParameters();
}

void LevelUpScene::updateScene(const sf::Time& deltaTime)
{
	for (auto& upg : upgrade) {
		upg.update();
	}
}

void LevelUpScene::drawScene(sf::RenderWindow& mainWindow)
{
	// Draw previous scene as background
	Locator::get<SceneManager>()->getLastScene()->drawScene(mainWindow);

	// Draw upgrades and texts
	for (const auto& upg : upgrade) {
		mainWindow.draw(upg);
	}

	mainWindow.draw(levelUpText);
	mainWindow.draw(infoText);

	mainWindow.draw(rarityFrame);

	for (int i = 0; i < 4; ++i) {
		mainWindow.draw(rarityInfoText[i]);
		mainWindow.draw(rarityPercentInfoText[i]);
	}
}

void LevelUpScene::checkEvents(sf::Event newEvent)
{
	switch (newEvent.type)
	{
#if _DEBUG
	case sf::Event::KeyPressed:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
			rollUpgrades(*gameState);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
			gameState->increaseLuckBy(1);
			rollUpgrades(*gameState);
		}
		break;
#endif
	case sf::Event::MouseButtonPressed:
		mouseDown = true;
		break;
	case sf::Event::MouseButtonReleased:

		if (newEvent.mouseButton.button != 0 || !mouseDown) {
			break;
		}

		for (int i = 0; i < NUM_UPGRADES; ++i) {
			if (upgrade[i].isSelected() && gameState) {
				applyValueToState(upgrade[i].getInfo().parameter, upgrade[i].getRarityValue(), *gameState);
				Locator::get<SceneManager>()->changeScene(Scene::Game);
			}
		}

		mouseDown = false;

		break;
	}
}

void LevelUpScene::loadScene(){}
void LevelUpScene::restartScene(){}
void LevelUpScene::closeScene(){}

void LevelUpScene::rollUpgrades(GameState& state)
{
	gameState = &state;

	std::array<int ,4> probabilities = DEFAULT_PROBABILITIES;

	int luck = state.getLuck();

    if (luck > 0 && luck <= 16) {
        probabilities[0] -= luck * 5;
        probabilities[1] += luck * 2;
        probabilities[2] += luck * 2;
        probabilities[3] += luck;
	} else if (luck > 16 && luck <= 31) {
		int base = luck - 16;

		probabilities[0] = 0;
		probabilities[1] += 32 - base * 3;
		probabilities[2] += 32 + base * 2;
		probabilities[3] += luck; 
	} else if (luck > 31 && luck <= 65) {
		int base = luck - 31;

		probabilities[0] = 0;
		probabilities[1] = 0;
		probabilities[2] += 63 - base * 2;
		probabilities[3] += 32 + base * 2;
	} else if (luck > 65) {
		probabilities[0] = 0;
		probabilities[1] = 0;
		probabilities[2] = 0;
		probabilities[3] = 100;
	}

	updateRarityInfoStrings(probabilities);

	std::set<Upgrade::Parameter> usedParameters;
	for(auto & upg : upgrade) {
		Upgrade::Rarity rarity = rollRarity(probabilities);
		Upgrade::Info info = rollParameter(rarity, usedParameters);

		float current = getCurrentValue(info.parameter, state);

		upg.setRarity(rarity);
		upg.setInfo(info, current);

		usedParameters.insert(info.parameter);
	}
}

Upgrade::Rarity LevelUpScene::rollRarity(const std::array<int, 4>& probabilities)
{
	int total = 0;
	for (int prob : probabilities) {
		total += prob;
	}

	int roll = rand() % total;

	int sum = 0;
	for (int i = 0; i < probabilities.size(); ++i) {
		sum += probabilities[i];
		if (roll < sum) {
			return Upgrade::Rarity(i);
		}
	}

	return Upgrade::COMMON;
}

Upgrade::Info LevelUpScene::rollParameter(Upgrade::Rarity rarity, const std::set<Upgrade::Parameter>& usedParameters)
{
	std::vector<Upgrade::Info> availableUpgrades;

	switch (rarity) {
	case Upgrade::COMMON:
		availableUpgrades = filterUpgrades(commonUpgrades, usedParameters);
		break;
	case Upgrade::RARE:
		availableUpgrades = filterUpgrades(rareUpgrades, usedParameters);
		break;
	case Upgrade::EPIC:
		availableUpgrades = filterUpgrades(epicUpgrades, usedParameters);
		break;
	case Upgrade::LEGENDARY:
		availableUpgrades = filterUpgrades(legendaryUpgrades, usedParameters);
		break;
	default:
		availableUpgrades = filterUpgrades(commonUpgrades, usedParameters);
		break;
	}

	int index = rand() % availableUpgrades.size();
	return availableUpgrades[index];
}

std::vector<Upgrade::Info> LevelUpScene::filterUpgrades(const std::vector<Upgrade::Info>& upgrades, const std::set<Upgrade::Parameter>& usedParameters)
{
	std::vector<Upgrade::Info> filteredUpgrades;
	for (const auto& upgrade : upgrades) {
		if (usedParameters.find(upgrade.parameter) == usedParameters.end()) {
			if (upgrade.parameter == Upgrade::Heal && this->gameState->isFullHealth()) {
				continue;
			}

			filteredUpgrades.push_back(upgrade);
		}
	}
	return filteredUpgrades;
}

float LevelUpScene::getCurrentValue(Upgrade::Parameter parameter, GameState& state)
{
	switch (parameter) {
	case Upgrade::PlayerSpeed:
		return state.getPlayerAcceleration();
	case Upgrade::PlayerShotsPerSeconds:
		return state.getPlayerShotsPerSecond();
	case Upgrade::PlayerDamage:
		return state.getPlayerDamage();
	case Upgrade::ScoreMultiplier:
		return state.getScoreMultiplier();
	case Upgrade::Heal:
		return state.getHealth();
	case Upgrade::MaxHealth:
		return state.getMaxHealth();
	case Upgrade::ExperienceMultiplier:
		return state.getExperienceMultiplier();
	case Upgrade::Luck:
		return state.getLuck();
	default:
		return -1.0f;
	}
}

void LevelUpScene::applyValueToState(Upgrade::Parameter parameter, float value, GameState& state)
{
	switch (parameter) {
	case Upgrade::PlayerSpeed:
		state.increasePlayerAccelerationBy(value);
		break;
	case Upgrade::PlayerShotsPerSeconds:
		state.increasePlayerShotsPerSecondBy(value);
		break;
	case Upgrade::PlayerDamage:
		state.increasePlayerDamageBy(value);
		break;
	case Upgrade::ScoreMultiplier:
		state.increaseScoreMultiplierBy(value);
		break;
	case Upgrade::Heal:
		state.increaseHealthBy(value);
		break;
	case Upgrade::MaxHealth:
		state.increaseMaxHealthBy(value);
		break;
	case Upgrade::ExperienceMultiplier:
		state.increaseExperienceMultiplierBy(value);
		break;
	case Upgrade::Luck:
		state.increaseLuckBy(value);
		break;
	default:
		break;
	}
}

void LevelUpScene::InitUpgradeParameters()
{
	Upgrade::Info upgradeInfo[8];

	upgradeInfo[0].parameter = Upgrade::PlayerSpeed;
	upgradeInfo[0].parameterName = "Movement\n Speed ";
	upgradeInfo[0].charSize = 18;
	upgradeInfo[0].commonValue = 200;
	upgradeInfo[0].rareValue = 350;
	upgradeInfo[0].epicValue = 600;
	upgradeInfo[0].legendaryValue = 1000;

	upgradeInfo[1].parameter = Upgrade::PlayerShotsPerSeconds;
	upgradeInfo[1].parameterName = "Shots per\n Second ";
	upgradeInfo[1].charSize = 18;
	upgradeInfo[1].commonValue = 0.5;
	upgradeInfo[1].rareValue = 1.2;
	upgradeInfo[1].epicValue = 2.5;
	upgradeInfo[1].legendaryValue = 5;

	upgradeInfo[2].parameter = Upgrade::PlayerDamage;
	upgradeInfo[2].parameterName = "Damage";
	upgradeInfo[2].charSize = 20;
	upgradeInfo[2].commonValue = 0;
	upgradeInfo[2].rareValue = 4;
	upgradeInfo[2].epicValue = 10;
	upgradeInfo[2].legendaryValue = 25;

	upgradeInfo[3].parameter = Upgrade::ScoreMultiplier;
	upgradeInfo[3].parameterName = "  Score  \nMultiplier";
	upgradeInfo[3].charSize = 18;
	upgradeInfo[3].commonValue = 0.1;
	upgradeInfo[3].rareValue = 0.2;
	upgradeInfo[3].epicValue = 0.5;
	upgradeInfo[3].legendaryValue = 1.5;

	upgradeInfo[4].parameter = Upgrade::Heal;
	upgradeInfo[4].parameterName = "Heal";
	upgradeInfo[4].charSize = 20;
	upgradeInfo[4].commonValue = 0;
	upgradeInfo[4].rareValue = 0;
	upgradeInfo[4].epicValue = 1;
	upgradeInfo[4].legendaryValue = 3;

	upgradeInfo[5].parameter = Upgrade::MaxHealth;
	upgradeInfo[5].parameterName = "Max Health";
	upgradeInfo[5].charSize = 18;
	upgradeInfo[5].commonValue = 0;
	upgradeInfo[5].rareValue = 0;
	upgradeInfo[5].epicValue = 0;
	upgradeInfo[5].legendaryValue = 1;

	upgradeInfo[6].parameter = Upgrade::ExperienceMultiplier;
	upgradeInfo[6].parameterName = "Experience\nMultiplier";
	upgradeInfo[6].charSize = 16;
	upgradeInfo[6].commonValue = 0.2;
	upgradeInfo[6].rareValue = 0.5;
	upgradeInfo[6].epicValue = 0.8;
	upgradeInfo[6].legendaryValue = 2.2;

	upgradeInfo[7].parameter = Upgrade::Luck;
	upgradeInfo[7].parameterName = "Luck";
	upgradeInfo[7].charSize = 20;
	upgradeInfo[7].commonValue = 0;
	upgradeInfo[7].rareValue = 1;
	upgradeInfo[7].epicValue = 2;
	upgradeInfo[7].legendaryValue = 5;

	for (int i = 0; i < 8; i++) {
		if (upgradeInfo[i].commonValue != 0) {
			commonUpgrades.push_back(upgradeInfo[i]);
		}

		if (upgradeInfo[i].rareValue != 0) {
			rareUpgrades.push_back(upgradeInfo[i]);
		}

		if (upgradeInfo[i].epicValue != 0) {
			epicUpgrades.push_back(upgradeInfo[i]);
		}

		if (upgradeInfo[i].legendaryValue != 0) {
			legendaryUpgrades.push_back(upgradeInfo[i]);
		}
	}

	rarityInfoText[0].setString("Common");
	rarityInfoText[1].setString("Rare");
	rarityInfoText[2].setString("Epic");
	rarityInfoText[3].setString("Legendary");

	for (int i = 0; i < 4; ++i) {
		rarityInfoText[i].setFont(Locator::get<GraphicService>()->getFont(GraphicService::Pixel));
		rarityInfoText[i].setFontSize(32);
		rarityInfoText[i].setOrigin(rarityInfoText[i].getLocalBounds().getSize().x / 2.f, 0);
		rarityPercentInfoText[i].setFont(Locator::get<GraphicService>()->getFont(GraphicService::Pixel));
		rarityPercentInfoText[i].setFontSize(20);
		
	}

	rarityInfoText[0].setColor(sf::Color::Green);
	rarityInfoText[1].setColor(sf::Color::Cyan);
	rarityInfoText[2].setColor(sf::Color(220, 0, 255));
	rarityInfoText[3].setColor(sf::Color(255, 200, 0));
}

void LevelUpScene::updateRarityInfoStrings(const std::array<int, 4>& probabilities)
{
	if (probabilities[3] == 0) {
		rarityInfoText[0].setPosition(sf::Vector2f(300, 850));
		rarityInfoText[1].setPosition(sf::Vector2f(510, 850));
		rarityInfoText[2].setPosition(sf::Vector2f(720, 850));
		rarityInfoText[3].setPosition(sf::Vector2f(1500, 850));

		rarityPercentInfoText[0].setPosition(sf::Vector2f(300, 890));
		rarityPercentInfoText[1].setPosition(sf::Vector2f(510, 890));
		rarityPercentInfoText[2].setPosition(sf::Vector2f(720, 890));
		rarityPercentInfoText[3].setPosition(sf::Vector2f(1500, 890));

		rarityFrame.setSize(sf::Vector2f(600, 75));
	} else {
		rarityInfoText[0].setPosition(sf::Vector2f(165, 850));
		rarityInfoText[1].setPosition(sf::Vector2f(380, 850));
		rarityInfoText[2].setPosition(sf::Vector2f(550, 850));
		rarityInfoText[3].setPosition(sf::Vector2f(800, 850));

		rarityPercentInfoText[0].setPosition(sf::Vector2f(165, 890));
		rarityPercentInfoText[1].setPosition(sf::Vector2f(380, 890));
		rarityPercentInfoText[2].setPosition(sf::Vector2f(550, 890));
		rarityPercentInfoText[3].setPosition(sf::Vector2f(800, 890));

		rarityFrame.setSize(sf::Vector2f(875,75));
	}

	rarityFrame.setOrigin(rarityFrame.getSize() / 2.f);

	for (int i = 0; i < 4; i++) {
		rarityPercentInfoText[i].setString(std::to_string(probabilities[i]) + "%");
		rarityPercentInfoText[i].setOrigin(rarityPercentInfoText[i].getLocalBounds().getSize().x / 2.f, 0);
	}
}
