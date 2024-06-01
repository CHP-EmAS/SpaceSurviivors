#include "GameState.h"
#include "GameObject.h"

#include <iostream>

bool GameState::isGameOver()
{
	return gameOver;
}

void GameState::addScore(int score)
{
	this->score += score;
	notifyObservers(SCORE_UPDATED, { NULL, this->score});
}

void GameState::decreaseHitPointsBy(int damage)
{
	hitPoints -= damage;

	if (hitPoints <= 0) {
		gameOver = true;
		notifyObservers(GAME_OVER, {});
	}
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
	std::cout << "Level Up! " << level << std::endl;

	experienceForLevelUp = experienceForLevelUp * 1.5;
	playerAcceleration += 200;
	playerShootInterval -= 0.05;

	std::cout << "Next Level by: " << experienceForLevelUp << std::endl;

	notifyObservers(LEVEL_UPDATED, { NULL, level });
	notifyObservers(MAX_EXPERIENCE_UPDATED, { NULL, experienceForLevelUp });
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

void GameState::setStartValues()
{
	gameOver = false;

	score = 0;
	experience = 0;
	experienceForLevelUp = 10;
	level = 1;

	notifyObservers(SCORE_UPDATED, { NULL, score });
	notifyObservers(EXPERIENCE_UPDATED, { NULL, experience });
	notifyObservers(MAX_EXPERIENCE_UPDATED, { NULL, experienceForLevelUp });
	notifyObservers(LEVEL_UPDATED, { NULL, level });

	playerAcceleration = 1500;
	playerShootInterval = 0.5;
	playerInvinciblyInterval = 1.5;
}
