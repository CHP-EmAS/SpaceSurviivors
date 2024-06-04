#pragma once

#include <string>
#include <vector>
#include <fstream>

class Highscore {
public:
    struct Entry {
        std::string name;
        int score;
    };

    Highscore();

    void addHighscore(const std::string& name, int score);
    void saveHighscores() const;
    void loadHighscores();
    const std::vector<Entry>& getHighscores() const;
    const bool isUnderTopThree(int score) const;

private:
    std::vector<Entry> highscores;
    std::string filename;

    static bool compareScores(const Entry& a, const Entry& b);
};
