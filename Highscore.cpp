#include "Highscore.h"
#include <algorithm>

Highscore::Highscore() : filename("data.space") {
    loadHighscores();
}

void Highscore::addHighscore(const std::string& name, int score) {
    highscores.push_back({ name, score });
    std::sort(highscores.begin(), highscores.end(), compareScores);

    if (highscores.size() > 3) {
        highscores.resize(3);
    }

    saveHighscores();
}

void Highscore::saveHighscores() const {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        for (const auto& entry : highscores) {
            size_t nameLength = entry.name.size();
            file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
            file.write(entry.name.data(), nameLength);
            file.write(reinterpret_cast<const char*>(&entry.score), sizeof(entry.score));
        }
        file.close();
    }
}

void Highscore::loadHighscores() {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        highscores.clear();
        while (file.peek() != EOF) {
            size_t nameLength;
            file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));

            std::string name(nameLength, ' ');
            file.read(&name[0], nameLength);

            int score;
            file.read(reinterpret_cast<char*>(&score), sizeof(score));

            highscores.push_back({ name, score });
        }
        file.close();
    }
}

const std::vector<Highscore::Entry>& Highscore::getHighscores() const {
    return highscores;
}

const bool Highscore::isUnderTopThree(int score) const
{
    if (highscores.size() < 3) {
        return true;
    }

    if (highscores[2].score < score) {
        return true;
    }

    return false;
}

bool Highscore::compareScores(const Entry& a, const Entry& b) {
    return a.score > b.score;
}