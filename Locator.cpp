#include "Locator.h"

SceneManager* Locator::sceneManager_ = nullptr;
GraphicService* Locator::graphicService_ = nullptr;
SoundManager* Locator::soundManager_ = nullptr;
HighscoreService* Locator::highscoreService_ = nullptr;

World* Locator::gameWorld_ = nullptr;
GameState* Locator::gameState_ = nullptr;

void Locator::provide(SceneManager* scene) {
	sceneManager_ = scene;
}

void Locator::provide(GraphicService* graphic) {
	graphicService_ = graphic;
}

void Locator::provide(SoundManager* sound)
{
	soundManager_ = sound;
}

void Locator::provide(HighscoreService* highscore)
{
	highscoreService_ = highscore;
}

void Locator::provide(World* gameWorld)
{
	gameWorld_ = gameWorld;
}

void Locator::provide(GameState* gameState)
{
	gameState_ = gameState;
}

SceneManager& Locator::getSceneManager()
{
	return *sceneManager_;
}

GraphicService& Locator::getGraphicService() {
	return *graphicService_;
}

SoundManager& Locator::getSoundManager()
{
	return *soundManager_;
}

HighscoreService& Locator::getHighscoreService()
{
	return *highscoreService_;
}

World& Locator::getGameWorld()
{
	return *gameWorld_;
}

GameState& Locator::getGameState()
{
	return *gameState_;
}
