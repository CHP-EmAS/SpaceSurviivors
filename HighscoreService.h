#pragma once

#include <string>
#include <vector>

class HighscoreService {
public:
	struct Entry {
		std::string name;
		unsigned long score = 0;
	};

	virtual bool isPersonalBest(unsigned long score) = 0;
	virtual unsigned long getPersonalHighscore() = 0;
	virtual bool submitScore(std::string name, unsigned long score) = 0;

	virtual const std::vector<Entry> getTopEntries(short limit) = 0;

protected:
	static bool compareScores(const Entry& a, const Entry& b) {
		return a.score > b.score;
	}
};