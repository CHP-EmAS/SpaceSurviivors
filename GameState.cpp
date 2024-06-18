#include <iostream>

#include "GameState.h"
#include "GameObject.h"

#include "LevelUp.h"
#include "Locator.h"

bool GameState::isGameOver()
{
	return gameOver;
}

void GameState::increaseScoreBy(int score)
{
	this->score += score * scoreMultiplier;
	notifyObservers(SCORE_UPDATED, { NULL, this->score});
}

void GameState::increaseScoreMultiplierBy(float multiplier)
{
	scoreMultiplier += multiplier;
}

void GameState::decreaseHealthBy(int damage)
{
	health -= damage;

	notifyObservers(HEALTH_UPDATED, {NULL, this->health });

	if (health <= 0) {
		gameOver = true;
		notifyObservers(GAME_OVER, {});
	}
}

void GameState::increaseHealthBy(int heal)
{
	if ((health + heal) < maxHealth) {
		health += heal;
	} else {
		health = maxHealth;
	}

	notifyObservers(HEALTH_UPDATED, { NULL, this->health });
}

void GameState::increaseMaxHealthBy(int health)
{
	maxHealth += health;
	this->health += health;

	notifyObservers(MAX_HEALTH_UPDATED, { NULL, this->maxHealth });
	notifyObservers(HEALTH_UPDATED, { NULL, this->health });
}

void GameState::increaseExperienceBy(int experienceToAdd)
{
	experience += experienceToAdd * experienceMultiplier;

	while (experience >= experienceForLevelUp) {
		experience = experience - experienceForLevelUp;
		increaseLevelByOne();
	}

	notifyObservers(EXPERIENCE_UPDATED, { NULL, this->experience });
}

void GameState::increaseExperienceMultiplierBy(float multiplier)
{
	experienceMultiplier += multiplier;
}

void GameState::increaseLevelByOne()
{
	level++;
	
	experienceForLevelUp = 7 * level * level;

	notifyObservers(LEVEL_UPDATED, { NULL, level });
	notifyObservers(MAX_EXPERIENCE_UPDATED, { NULL, experienceForLevelUp });

	static_cast<LevelUpScene*>(Locator::getSceneManager().getScene(Scene::Level_UP))->rollUpgrades(*this);
	Locator::getSceneManager().changeScene(Scene::Level_UP, false);
}

void GameState::increasePlayerAccelerationBy(float acceleration)
{
	playerAcceleration += acceleration;
}

void GameState::increasePlayerShotsPerSecondBy(float shotsPerSecond)
{
	playerShotsPerSecond += shotsPerSecond;
}

void GameState::increasePlayerDamageBy(float damage)
{
	playerDamage += damage;
}

void GameState::increaseLuckBy(int luck)
{
	this->luck += luck;
}

void GameState::increasePiercingBulletChanceBy(float chance)
{
	piercingBulletChance += chance;

	if (piercingBulletChance > 100.f) {
		piercingBulletChance = 100.f;
	}
}

void GameState::setStartValues()
{
	gameOver = false;

	score = 0;
	scoreMultiplier = 1;

	health = 3;
	maxHealth = 3;

	experience = 0;
	experienceForLevelUp = 20;
	experienceMultiplier = 1;
	level = 1;

	luck = 0;

	playerAcceleration = 1500;
	playerShotsPerSecond = 3;
	playerInvinciblyInterval = 1.5;
	playerDamage = 10;

	piercingBulletChance = 0;

	notifyObservers(SCORE_UPDATED, { NULL, score });
	notifyObservers(EXPERIENCE_UPDATED, { NULL, experience });
	notifyObservers(MAX_EXPERIENCE_UPDATED, { NULL, experienceForLevelUp });
	notifyObservers(LEVEL_UPDATED, { NULL, level });
	notifyObservers(MAX_HEALTH_UPDATED, { NULL, maxHealth });
	notifyObservers(HEALTH_UPDATED, { NULL, health });
}
