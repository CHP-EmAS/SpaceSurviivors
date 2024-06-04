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
	Upgrade::Rarity rollRarity(const std::array<int, 4>& probabilities);
	Upgrade::Info rollParameter(Upgrade::Rarity rarity);
	float getCurrentValue(Upgrade::Parameter parameter, GameState& state);
	void applyValueToState(Upgrade::Parameter parameter, float value, GameState& state);

	void InitUpgradeParameters();

	Upgrade upgrade[3];

	std::vector<Upgrade::Info> commonUpgrades;
	std::vector<Upgrade::Info> rareUpgrades;
	std::vector<Upgrade::Info> epicUpgrades;
	std::vector<Upgrade::Info> legendaryUpgrades;

	DropShadowText levelUpText;
	DropShadowText infoText;

	bool mouseDown;

	GameState* gameState;
};

