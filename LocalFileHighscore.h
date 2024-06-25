#pragma once

#include "HighscoreService.h"

class LocalFileHighscore : public HighscoreService
{
public:
	LocalFileHighscore();

	bool isPersonalBest(unsigned long score) override;
	bool submitScore(std::string name, unsigned long score) override;

	unsigned long getPersonalHighscore() override;
	const std::vector<Entry> getTopEntries(short limit) override;

private:
	bool saveHighscores();
	bool loadHighscores();

	std::vector<Entry> highscoreList;
};

