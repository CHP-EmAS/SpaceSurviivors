#include "LocalFileHighscore.h"

#include <fstream>
#include <algorithm>

static const std::string HIGHSCORE_FILE = "data.space";

LocalFileHighscore::LocalFileHighscore()
{
	loadHighscores();
}

bool LocalFileHighscore::isPersonalBest(unsigned long score)
{
    if (highscoreList.size() < 3) {
        return true;
    }

    if (highscoreList[2].score < score) {
        return true;
    }

    return false;
}

bool LocalFileHighscore::submitScore(std::string name, unsigned long score)
{
    highscoreList.push_back({ name, score });
    return saveHighscores();
}

unsigned long LocalFileHighscore::getPersonalHighscore()
{
	return 0;
}

const std::vector<HighscoreService::Entry> LocalFileHighscore::getTopEntries(short limit)
{
    std::vector<HighscoreService::Entry> copy(highscoreList);
    copy.resize(limit);

    return copy;
}

bool LocalFileHighscore::saveHighscores()
{
    std::sort(highscoreList.begin(), highscoreList.end(), compareScores);

    std::ofstream file(HIGHSCORE_FILE, std::ios::binary);

    if (file.is_open()) {

        for (const auto& entry : highscoreList) {
            size_t nameLength = entry.name.size();
            file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));

            file.write(entry.name.data(), nameLength);

            file.write(reinterpret_cast<const char*>(&entry.score), sizeof(entry.score));
        }

        file.close();
    } else {
        return false;
    }

    return true;
}

bool LocalFileHighscore::loadHighscores()
{
    std::ifstream file(HIGHSCORE_FILE, std::ios::binary);

    if (file.is_open()) {

        highscoreList.clear();

        while (file.peek() != EOF) {
            size_t nameLength;
            file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));

            std::string name(nameLength, ' ');
            file.read(&name[0], nameLength);

            unsigned long score;
            file.read(reinterpret_cast<char*>(&score), sizeof(score));

            highscoreList.push_back({ name, score });
            std::sort(highscoreList.begin(), highscoreList.end(), compareScores);
        }

        file.close();
    } else {
        return false;
    }

    return true;
}


