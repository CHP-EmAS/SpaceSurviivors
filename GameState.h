#pragma once

#include <SFML/System.hpp>

class GameState
{
public:
	bool isGameOver() const;

	const sf::Time getGameTime() const { return gameTime; };

	int getScore() const { return score; }
	float getScoreMultiplier() const { return scoreMultiplier; }
	
	int getHealth() const { return health; }
	int getMaxHealth() const { return maxHealth; }
	bool isFullHealth() const { return health == maxHealth; }
	
	int getLuck() const { return luck; };
	
	int getExperience() const { return experience; }
	int getExperienceForLevelUp() const { return experienceForLevelUp; }
	float getExperienceMultiplier() const { return experienceMultiplier; }
	int getLevel() const { return level; }
	
	float getPlayerAcceleration() const { return playerAcceleration; }
	float getPlayerShotsPerSecond() const { return playerShotsPerSecond; }
	float getPlayerInvinciblyInterval() const { return playerInvinciblyInterval; }
	int getPlayerDamage() const { return playerDamage; }

	void updateGameTime(const sf::Time& deltaTime);

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

	sf::Time gameTime;
};

