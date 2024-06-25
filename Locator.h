#pragma once

#include "SceneManager.h"
#include "GraphicService.h"
#include "SoundManager.h"
#include "HighscoreService.h"

class Locator
{
public:
	static void provide(SceneManager* scene);
	static void provide(GraphicService* graphic);
	static void provide(SoundManager* sound);
	static void provide(HighscoreService* highscore);

	static SceneManager& getSceneManager();
	static GraphicService& getGraphicService();
	static SoundManager& getSoundManager();
	static HighscoreService& getHighscoreService();

private:
	static SceneManager* sceneManager_;
	static GraphicService* graphicService_;
	static SoundManager* soundManager_;
	static HighscoreService* highscoreService_;
};



