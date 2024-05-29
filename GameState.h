#pragma once

#include "Observable.h"

class GameState : public Observable
{
public:
	int getScore() const;
	void addScore(int score);

	void reset();
private: 
	int score;
};

