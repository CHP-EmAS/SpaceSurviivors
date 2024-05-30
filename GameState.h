#pragma once

#include "Observable.h"

class GameState : public Observable
{
public:
	int getScore() const { return score; }
	int getExperience() const { return experience; }
	int getExperienceForLevelUp() const { return experienceForLevelUp; }
	int getLevel() const { return level; }
	float getPlayerAcceleration() { return playerAcceleration; }
	float getPlayerShootInterval() { return playerShootInterval; }
	float getPlayerInvinciblyInterval() { return playerInvinciblyInterval; }

	void addScore(int score);
	void addExperience(int experience);
	void increaseLevel();
	void setPlayerAcceleration(float acceleration);
	void setPlayerShootInterval(float shootInterval);
	void setPlayerInvinciblyInterval(float invinciblyInterval);

	void setStartValues();
private: 
	int score;
	int experience;
	int experienceForLevelUp;
	short level;
	
	float playerAcceleration;
	float playerShootInterval;
	float playerInvinciblyInterval;
};

