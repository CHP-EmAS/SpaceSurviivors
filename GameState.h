#pragma once

#include "Observable.h"

class GameState : public Observable
{
public:
	bool isGameOver();

	inline int getScore() const { return score; }
	inline float getScoreMultiplier() const { return scoreMultiplier; }

	inline int getHealth() const { return health; }
	inline int getMaxHealth() const { return maxHealth; }

	inline int getLuck() { return luck; };

	inline int getExperience() const { return experience; }
	inline int getExperienceForLevelUp() const { return experienceForLevelUp; }
	inline float getExperienceMultiplier() const { return experienceMultiplier; }
	inline int getLevel() const { return level; }

	inline float getPlayerAcceleration() { return playerAcceleration; }
	inline float getPlayerShotsPerSecond() { return playerShotsPerSecond; }
	inline float getPlayerInvinciblyInterval() { return playerInvinciblyInterval; }
	inline int getPlayerDamage() { return playerDamage; }

	
	void increaseScoreBy(int score);
	void increaseScoreMultiplierBy(float multiplier);

	void increaseHealthBy(int heal);
	void increaseMaxHealthBy(int health);
	void decreaseHealthBy(int damage);

	void increaseExperienceBy(int experience);
	void increaseExperienceMultiplierBy(float multiplier);
	void increaseLevelByOne();

	void increasePlayerAccelerationBy(float acceleration);
	void increasePlayerShotsPerSecondBy(float shotsPerSecond);
	void increasePlayerDamageBy(float damage);

	void increaseLuckBy(int luck);

	void setStartValues();
private: 
	bool gameOver;

	int score;
	float scoreMultiplier;

	int health;
	int maxHealth;

	int luck;

	int experience;
	int experienceForLevelUp;
	float experienceMultiplier;
	int level;
	
	float playerAcceleration;
	float playerShotsPerSecond;
	float playerInvinciblyInterval;
	int playerDamage;
};

