#include "LevelUp.h"

#include "Locator.h"

LevelUpScene::LevelUpScene() : Scene(Level_UP)
{
	for (int i = 0; i < 3; i++) {
		upgrade[i].setScale(1.5, 1.5);
		upgrade[i].setPosition((250 * i) + (62.5 * (i + 1)), 400);
	}

	sf::Text text = sf::Text("Level Up!", Locator::getGraphicService().getFont(GraphicService::Pixel), 55);
	text.setLineSpacing(2);
	text.setFillColor(sf::Color(255,223,0));
	levelUpText.setText(text);
	levelUpText.setOrigin(text.getLocalBounds().width / 2, 0);
	levelUpText.setPosition(WINDOW_SIZE / 2, 200);
	levelUpText.setShadowOffset(5);

	text = sf::Text("Choose one of the upgrades", Locator::getGraphicService().getFont(GraphicService::Pixel), 24);
	infoText.setText(text);
	infoText.setOrigin(text.getLocalBounds().width / 2, 0);
	infoText.setPosition(WINDOW_SIZE / 2, 280);
	infoText.setShadowOffset(3);

	mouseDown = false;

	InitUpgradeParameters();
}

void LevelUpScene::updateScene(sf::Time deltaTime)
{
	for (int i = 0; i < 3; i++) {
		upgrade[i].update();
	}
}

void LevelUpScene::drawScene(sf::RenderWindow& mainWindow)
{
	Locator::getSceneManager().getLastScene()->drawScene(mainWindow);

	for (int i = 0; i < 3; i++) {
		mainWindow.draw(upgrade[i]);
	}

	mainWindow.draw(levelUpText);
	mainWindow.draw(infoText);
}

void LevelUpScene::checkEvents(sf::Event newEvent)
{
	switch (newEvent.type)
	{
	case sf::Event::KeyPressed:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
			rollUpgrades(*debugState);
		}
		break;
	case sf::Event::MouseButtonPressed:
		mouseDown = true;
		break;
	case sf::Event::MouseButtonReleased:

		if (newEvent.mouseButton.button != 0 || !mouseDown) {
			break;
		}

		if (upgrade[0].isSelected()) {
			Locator::getSceneManager().changeScene(Scene::Game);
		} else if (upgrade[1].isSelected()) {
			Locator::getSceneManager().changeScene(Scene::Game);
		} else if (upgrade[2].isSelected()) {
			Locator::getSceneManager().changeScene(Scene::Game);
		}

		mouseDown = false;

		break;
	}
}

void LevelUpScene::loadScene()
{
}

void LevelUpScene::restartScene()
{

}

void LevelUpScene::closeScene()
{
}

void LevelUpScene::rollUpgrades(GameState& state)
{
	debugState = &state;

	int probabilities[4] = { 80, 15, 5, 0 };

	int luck = std::min(16, state.getLuck());
	if (luck > 0) {
		probabilities[0] = probabilities[0] - luck * 5;
		probabilities[1] = probabilities[1] + luck * 2;
		probabilities[2] = probabilities[2] + luck * 2;
		probabilities[3] = probabilities[3] + luck;
	}

	for (int i = 0; i < 3; i++) {
		Upgrade::Rarity rarity = rollRarity(probabilities);
		upgrade[i].setRarity(rarity);
		upgrade[i].setInfo(rollParameter(rarity));
	}
}

Upgrade::Rarity LevelUpScene::rollRarity(int probabilities[4])
{
	int total = 0;

	for (int i = 0; i < 4; i++) {
		total += probabilities[i];
	}

	int roll = rand() % total;

	int sum = 0;
	for (int i = 0; i < 4; ++i) {
		sum += probabilities[i];
		if (roll < sum) {
			return Upgrade::Rarity(i);
		}
	}

	return Upgrade::COMMON;
}

Upgrade::UpgradeInfo LevelUpScene::rollParameter(Upgrade::Rarity rarity)
{
	int index;

	switch(rarity) {
	case Upgrade::COMMON:
		index = rand() % (int)commonUpgrades.size();
		return commonUpgrades[index];
	case Upgrade::RARE:
		index = rand() % (int)rareUpgrades.size();
		return rareUpgrades[index];
		break;
	case Upgrade::EPIC:
		index = rand() % (int)epicUpgrades.size();
		return epicUpgrades[index];
		break;
	case Upgrade::LEGENDARY:
		index = rand() % (int)legendaryUpgrades.size();
		return legendaryUpgrades[index];
		break;
	}
}

void LevelUpScene::InitUpgradeParameters()
{
	Upgrade::UpgradeInfo upgradeInfo[7];

	upgradeInfo[0].parameter = Upgrade::PlayerSpeed;
	upgradeInfo[0].parameterName = "Movement\n Speed ";
	upgradeInfo[0].charSize = 18;
	upgradeInfo[0].commonValue = 100;
	upgradeInfo[0].rareValue = 250;
	upgradeInfo[0].epicValue = 500;
	upgradeInfo[0].legendaryValue = 1000;

	upgradeInfo[1].parameter = Upgrade::PlayerShotsPerSeconds;
	upgradeInfo[1].parameterName = "Shots per\n Second ";
	upgradeInfo[1].charSize = 18;
	upgradeInfo[1].commonValue = 0.2;
	upgradeInfo[1].rareValue = 0.5;
	upgradeInfo[1].epicValue = 1;
	upgradeInfo[1].legendaryValue = 2;

	upgradeInfo[2].parameter = Upgrade::ScoreMultiplier;
	upgradeInfo[2].parameterName = "  Score  \nMultiplier";
	upgradeInfo[2].charSize = 18;
	upgradeInfo[2].commonValue = 0.1;
	upgradeInfo[2].rareValue = 0.2;
	upgradeInfo[2].epicValue = 0.5;
	upgradeInfo[2].legendaryValue = 0.8;

	upgradeInfo[3].parameter = Upgrade::Heal;
	upgradeInfo[3].parameterName = "Heal";
	upgradeInfo[3].charSize = 20;
	upgradeInfo[3].commonValue = 0;
	upgradeInfo[3].rareValue = 0;
	upgradeInfo[3].epicValue = 1;
	upgradeInfo[3].legendaryValue = 3;

	upgradeInfo[4].parameter = Upgrade::MaxHealth;
	upgradeInfo[4].parameterName = "Max Health";
	upgradeInfo[4].charSize = 18;
	upgradeInfo[4].commonValue = 0;
	upgradeInfo[4].rareValue = 0;
	upgradeInfo[4].epicValue = 0;
	upgradeInfo[4].legendaryValue = 1;

	upgradeInfo[5].parameter = Upgrade::ExperienceMultiplier;
	upgradeInfo[5].parameterName = "Experience\nMultiplier";
	upgradeInfo[5].charSize = 16;
	upgradeInfo[5].commonValue = 0.2;
	upgradeInfo[5].rareValue = 0.5;
	upgradeInfo[5].epicValue = 0.8;
	upgradeInfo[5].legendaryValue = 1.2;

	upgradeInfo[6].parameter = Upgrade::Luck;
	upgradeInfo[6].parameterName = "Luck";
	upgradeInfo[6].charSize = 20;
	upgradeInfo[6].commonValue = 0;
	upgradeInfo[6].rareValue = 1;
	upgradeInfo[6].epicValue = 2;
	upgradeInfo[6].legendaryValue = 3;

	for (int i = 0; i < 7; i++) {
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
