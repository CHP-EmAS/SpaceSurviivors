#include <iostream>

#include "GameState.h"
#include "GameObject.h"

#include "LevelUp.h"
#include "Locator.h"

bool GameState::isGameOver()
{
	return gameOver;
}

void GameState::addScore(int score)
{
	this->score += score;
	notifyObservers(SCORE_UPDATED, { NULL, this->score});
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

void GameState::increaseMaxHealth()
{
	maxHealth++;
	health++;

	notifyObservers(MAX_HEALTH_UPDATED, { NULL, this->maxHealth });
	notifyObservers(HEALTH_UPDATED, { NULL, this->health });
}

void GameState::addExperience(int experienceToAdd)
{
	experience += experienceToAdd;

	while (experience >= experienceForLevelUp) {
		experience = experience - experienceForLevelUp;
		increaseLevel();
	}

	notifyObservers(EXPERIENCE_UPDATED, { NULL, this->experience });
}

void GameState::increaseLevel()
{
	level++;
	
	experienceForLevelUp = experienceForLevelUp * 1.5;

	//playerAcceleration += 200;
	//playerShootInterval -= 0.05;

	notifyObservers(LEVEL_UPDATED, { NULL, level });
	notifyObservers(MAX_EXPERIENCE_UPDATED, { NULL, experienceForLevelUp });

	static_cast<LevelUpScene*>(Locator::getSceneManager().getScene(Scene::Level_UP))->rollUpgrades(*this);
	Locator::getSceneManager().changeScene(Scene::Level_UP, false);
}

void GameState::setPlayerAcceleration(float acceleration)
{
	playerAcceleration = acceleration;
}

void GameState::setPlayerShootInterval(float shootInterval)
{
	playerShootInterval = shootInterval;
}


void GameState::setPlayerInvinciblyInterval(float invinciblyInterval)
{
	playerInvinciblyInterval = invinciblyInterval;
}

void GameState::increaseLuckBy(int luck)
{
	this->luck += luck;
}

void GameState::setStartValues()
{
	gameOver = false;

	score = 0;
	experience = 0;
	experienceForLevelUp = 10;
	level = 1;
	health = 3;
	maxHealth = 3;

	luck = 16;

	notifyObservers(SCORE_UPDATED, { NULL, score });
	notifyObservers(EXPERIENCE_UPDATED, { NULL, experience });
	notifyObservers(MAX_EXPERIENCE_UPDATED, { NULL, experienceForLevelUp });
	notifyObservers(LEVEL_UPDATED, { NULL, level });
	notifyObservers(MAX_HEALTH_UPDATED, { NULL, maxHealth });
	notifyObservers(HEALTH_UPDATED, { NULL, health });

	playerAcceleration = 1500;
	playerShootInterval = 0.5;
	playerInvinciblyInterval = 1.5;
}
