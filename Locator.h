#pragma once

#include "SceneManager.h"
#include "GraphicService.h"

class Locator
{
public:
	static void provide(SceneManager* scene);
	static void provide(GraphicService* graphic);


	static SceneManager& getSceneManager();
	static GraphicService& getGraphicService();

private:
	static SceneManager* sceneManager_;
	static GraphicService* graphicService_;
};



