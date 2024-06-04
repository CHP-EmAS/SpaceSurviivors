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
	sf::Text text = sf::Text("Level Up!", Locator::getGraphicService().getFont(GraphicService::Pixel), 55);
	text.setLineSpacing(2);
	text.setFillColor(sf::Color(255,223,0));
	levelUpText.setText(text);
	levelUpText.setOrigin(text.getLocalBounds().width / 2, 0);
	levelUpText.setPosition(WINDOW_SIZE / 2, 200);
	levelUpText.setShadowOffset(5);

	// Initialize info text
	text = sf::Text("Choose one of the upgrades", Locator::getGraphicService().getFont(GraphicService::Pixel), 24);
	infoText.setText(text);
	infoText.setOrigin(text.getLocalBounds().width / 2, 0);
	infoText.setPosition(WINDOW_SIZE / 2, 280);
	infoText.setShadowOffset(3);

	InitUpgradeParameters();
}

void LevelUpScene::updateScene(sf::Time deltaTime)
{
	for (auto& upg : upgrade) {
		upg.update();
	}
}

void LevelUpScene::drawScene(sf::RenderWindow& mainWindow)
{
	// Draw previous scene as background
	Locator::getSceneManager().getLastScene()->drawScene(mainWindow);

	// Draw upgrades and texts
	for (const auto& upg : upgrade) {
		mainWindow.draw(upg);
	}
	mainWindow.draw(levelUpText);
	mainWindow.draw(infoText);
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
				Locator::getSceneManager().changeScene(Scene::Game);
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

	int luck = std::min(16, state.getLuck());
    if (luck > 0) {
        probabilities[0] -= luck * 5;
        probabilities[1] += luck * 2;
        probabilities[2] += luck * 2;
        probabilities[3] += luck;
    }

	for(auto & upg : upgrade) {
		Upgrade::Rarity rarity = rollRarity(probabilities);
		Upgrade::Info info = rollParameter(rarity);

		float current = getCurrentValue(info.parameter, state);

		upg.setRarity(rarity);
		upg.setInfo(info, current);
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

Upgrade::Info LevelUpScene::rollParameter(Upgrade::Rarity rarity)
{
	int index;
	switch (rarity) {
	case Upgrade::COMMON:
		index = rand() % commonUpgrades.size();
		return commonUpgrades[index];
	case Upgrade::RARE:
		index = rand() % rareUpgrades.size();
		return rareUpgrades[index];
	case Upgrade::EPIC:
		index = rand() % epicUpgrades.size();
		return epicUpgrades[index];
	case Upgrade::LEGENDARY:
		index = rand() % legendaryUpgrades.size();
		return legendaryUpgrades[index];
	default:
		return commonUpgrades[0];
	}
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
	upgradeInfo[1].rareValue = 1.1;
	upgradeInfo[1].epicValue = 2;
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
	upgradeInfo[3].legendaryValue = 2;

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
	upgradeInfo[7].commonValue = 1;
	upgradeInfo[7].rareValue = 2;
	upgradeInfo[7].epicValue = 3;
	upgradeInfo[7].legendaryValue = 7;

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
}
