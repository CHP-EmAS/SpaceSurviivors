#include "Locator.h"

SceneManager* Locator::sceneManager_ = nullptr;
GraphicService* Locator::graphicService_ = nullptr;
SoundManager* Locator::soundManager_ = nullptr;

void Locator::provide(SceneManager* scene) {
	Locator::sceneManager_ = scene;
}

void Locator::provide(GraphicService* graphic) {
	Locator::graphicService_ = graphic;
}

void Locator::provide(SoundManager* sound)
{
	Locator::soundManager_ = sound;
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
