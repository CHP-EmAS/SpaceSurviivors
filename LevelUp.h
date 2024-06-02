#pragma once

#include "Scene.h"
#include "Upgrade.h"
#include "DropShadowText.h"
#include "GameState.h"

class LevelUpScene : public Scene
{
public:
	LevelUpScene();

	void updateScene(sf::Time deltaTime) override;
	void drawScene(sf::RenderWindow& mainWindow) override;
	void checkEvents(sf::Event newEvent) override;
	void loadScene() override;
	void restartScene() override;
	void closeScene() override;

	void rollUpgrades(GameState& state);

private:
	Upgrade::Rarity rollRarity(int probabilities[4]);
	Upgrade::UpgradeInfo rollParameter(Upgrade::Rarity rarity);

	void InitUpgradeParameters();

	Upgrade upgrade[3];

	std::vector<Upgrade::UpgradeInfo> commonUpgrades;
	std::vector<Upgrade::UpgradeInfo> rareUpgrades;
	std::vector<Upgrade::UpgradeInfo> epicUpgrades;
	std::vector<Upgrade::UpgradeInfo> legendaryUpgrades;

	DropShadowText levelUpText;
	DropShadowText infoText;

	bool mouseDown;

	GameState* debugState;
};

