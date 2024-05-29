#include "GameState.h"
#include "GameObject.h"

int GameState::getScore() const
{
	return score;
}

void GameState::addScore(int score)
{
	this->score += score;
	notifyObservers(NULL, GAME_STATE_UPDATED);
}

void GameState::reset()
{
	score = 0;
	notifyObservers(NULL, GAME_STATE_UPDATED);
}
