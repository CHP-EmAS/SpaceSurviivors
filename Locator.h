#pragma once

#include "SceneManager.h"
#include "GraphicService.h"
#include "SoundManager.h"
#include "HighscoreService.h"

#include "World.h"

class Locator
{
public:
	static void provide(SceneManager* scene);
	static void provide(GraphicService* graphic);
	static void provide(SoundManager* sound);
	static void provide(HighscoreService* highscore);

	static void provide(World* gameWorld);
	static void provide(GameState* gameState);

	static SceneManager& getSceneManager();
	static GraphicService& getGraphicService();
	static SoundManager& getSoundManager();
	static HighscoreService& getHighscoreService();

	static World& getGameWorld();
	static GameState& getGameState();

private:
	static SceneManager* sceneManager_;
	static GraphicService* graphicService_;
	static SoundManager* soundManager_;
	static HighscoreService* highscoreService_;

	static World* gameWorld_;
	static GameState* gameState_;
};



