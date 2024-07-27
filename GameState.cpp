#include <iostream>

#include "GameState.h"
#include "GameObject.h"

#include "LevelUp.h"
#include "Locator.h"

bool GameState::isGameOver() const
{
	return gameOver;
}

void GameState::updateGameTime(sf::Time deltaTime)
{
	gameTime += deltaTime;
}

void GameState::increaseScoreBy(int score)
{
	this->score += score * scoreMultiplier;
	broadcastEvent(Event::Event(Event::SCORE_UPDATED, this->score));
}

void GameState::increaseScoreMultiplierBy(float multiplier)
{
	scoreMultiplier += multiplier;
}

void GameState::decreaseHealthBy(int damage)
{
	health -= damage;

	broadcastEvent(Event::Event(Event::HEALTH_UPDATED, this->health));

	if (health <= 0) {
		gameOver = true;
		broadcastEvent(Event::Event(Event::GAME_OVER));
	}
}

void GameState::increaseHealthBy(int heal)
{
	if ((health + heal) < maxHealth) {
		health += heal;
	} else {
		health = maxHealth;
	}

	broadcastEvent(Event::Event(Event::HEALTH_UPDATED, this->health));
}

void GameState::increaseMaxHealthBy(int health)
{
	maxHealth += health;
	this->health += health;

	broadcastEvent(Event::Event(Event::MAX_HEALTH_UPDATED, this->maxHealth));
	broadcastEvent(Event::Event(Event::HEALTH_UPDATED, this->health));
}

void GameState::increaseExperienceBy(int experienceToAdd)
{
	experience += experienceToAdd * experienceMultiplier;

	while (experience >= experienceForLevelUp) {
		experience = experience - experienceForLevelUp;
		increaseLevelByOne();
	}

	broadcastEvent(Event::Event(Event::EXPERIENCE_UPDATED, this->experience));
}

void GameState::increaseExperienceMultiplierBy(float multiplier)
{
	experienceMultiplier += multiplier;
}

void GameState::increaseLevelByOne()
{
	level++;
	
	experienceForLevelUp = 7 * level * level;

	broadcastEvent(Event::Event(Event::LEVEL_UPDATED, this->level));
	broadcastEvent(Event::Event(Event::MAX_EXPERIENCE_UPDATED, this->experienceForLevelUp));

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

void GameState::setStartValues()
{
	gameOver = false;
	gameTime = sf::Time::Zero;

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

	broadcastEvent(Event::Event(Event::SCORE_UPDATED, this->score));
	broadcastEvent(Event::Event(Event::LEVEL_UPDATED, this->level));
	broadcastEvent(Event::Event(Event::HEALTH_UPDATED, this->health));
	broadcastEvent(Event::Event(Event::MAX_HEALTH_UPDATED, this->maxHealth));
	broadcastEvent(Event::Event(Event::EXPERIENCE_UPDATED, this->experience));
	broadcastEvent(Event::Event(Event::MAX_EXPERIENCE_UPDATED, this->experienceForLevelUp));
}


