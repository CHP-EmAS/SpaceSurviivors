#pragma once

#include "Observable.h"

class GameState : public Observable
{
public:
	bool isGameOver();
	int getScore() const { return score; }
	int getHitPoints() const { return hitPoints; }
	int getExperience() const { return experience; }
	int getExperienceForLevelUp() const { return experienceForLevelUp; }
	int getLevel() const { return level; }
	float getPlayerAcceleration() { return playerAcceleration; }
	float getPlayerShootInterval() { return playerShootInterval; }
	float getPlayerInvinciblyInterval() { return playerInvinciblyInterval; }

	void addScore(int score);
	void decreaseHitPointsBy(int damage);
	void addExperience(int experience);
	void increaseLevel();
	void setPlayerAcceleration(float acceleration);
	void setPlayerShootInterval(float shootInterval);
	void setPlayerInvinciblyInterval(float invinciblyInterval);

	void setStartValues();
private: 
	bool gameOver;

	int score;

	int hitPoints;

	int experience;
	int experienceForLevelUp;
	short level;
	
	float playerAcceleration;
	float playerShootInterval;
	float playerInvinciblyInterval;
};

