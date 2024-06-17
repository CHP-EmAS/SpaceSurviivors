#pragma once

#include "SceneManager.h"
#include "GraphicService.h"
#include "SoundManager.h"

class Locator
{
public:
	static void provide(SceneManager* scene);
	static void provide(GraphicService* graphic);
	static void provide(SoundManager* sound);

	static SceneManager& getSceneManager();
	static GraphicService& getGraphicService();
	static SoundManager& getSoundManager();

private:
	static SceneManager* sceneManager_;
	static GraphicService* graphicService_;
	static SoundManager* soundManager_;
};



