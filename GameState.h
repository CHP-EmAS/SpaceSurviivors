#pragma once

#include "Observable.h"

class GameState : public Observable
{
public:
	bool isGameOver();
	int getScore() const { return score; }
	int getHealth() const { return health; }
	int getMaxHealth() const { return maxHealth; }
	int getExperience() const { return experience; }
	int getExperienceForLevelUp() const { return experienceForLevelUp; }
	int getLevel() const { return level; }
	float getPlayerAcceleration() { return playerAcceleration; }
	float getPlayerShootInterval() { return playerShootInterval; }
	float getPlayerInvinciblyInterval() { return playerInvinciblyInterval; }
	int getLuck() { return luck; };

	void addScore(int score);
	void decreaseHealthBy(int damage);
	void increaseMaxHealth();
	void addExperience(int experience);
	void increaseLevel();
	void setPlayerAcceleration(float acceleration);
	void setPlayerShootInterval(float shootInterval);
	void setPlayerInvinciblyInterval(float invinciblyInterval);
	void increaseLuckBy(int luck);

	void setStartValues();
private: 
	bool gameOver;

	int score;
	float scoreMultiplier;

	int health;
	int maxHealth;

	int experience;
	int experienceForLevelUp;
	float experienceMultiplier;
	int level;
	
	float playerAcceleration;
	float playerShootInterval;
	float playerInvinciblyInterval;

	int luck;
};

