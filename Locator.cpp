#include "Locator.h"

SceneManager* Locator::sceneManager_ = nullptr;
GraphicService* Locator::graphicService_ = nullptr;
SoundManager* Locator::soundManager_ = nullptr;
HighscoreService* Locator::highscoreService_ = nullptr;

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
