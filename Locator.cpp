#include "Locator.h"

SceneManager* Locator::sceneManager_ = nullptr;
GraphicService* Locator::graphicService_ = nullptr;

void Locator::provide(SceneManager* scene) {
	Locator::sceneManager_ = scene;
}

void Locator::provide(GraphicService* graphic) {
	Locator::graphicService_ = graphic;
}

SceneManager& Locator::getSceneManager()
{
	return *sceneManager_;
}

GraphicService& Locator::getGraphicService() {
	return *graphicService_;
}