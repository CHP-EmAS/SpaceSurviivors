#include <SFML/Graphics.hpp>
#include <Steam/steam_api.h>

#include <thread>

#include "Defines.h"

#include "Locator.h"
#include "SceneManager.h"
#include "EmbeddedGraphicLoader.h"
#include "LocalFileHighscore.h"
#include "SoundManager.h"

static int mainLoop()
{
	SteamAPI_Init();

	if (SteamAPI_IsSteamRunning()) {
		std::cout << "Steam is running!" << std::endl;
	} else {
		std::cout << "Steam is not running!" << std::endl;
	}

    srand(time(NULL));

	EmbeddedGraphicLoader graphicLoader = EmbeddedGraphicLoader();
	Locator::provide(&graphicLoader);
	
	SoundManager soundManager = SoundManager();
	Locator::provide(&soundManager);
	soundManager.changeBackgroundMusic();

	LocalFileHighscore highscoreService = LocalFileHighscore();
	Locator::provide(&highscoreService);

	SceneManager sceneManager =SceneManager();
	Locator::provide(&sceneManager);
	sceneManager.setWindowMode(true, false);
	sceneManager.initScenes();
	sceneManager.changeScene(Scene::GameOver, false);

	sf::Clock drawClock;
	sf::Clock updateClock;
	sf::Clock fpsClock;

	sf::Int64 drawWaitDelay = 1000000 / FPS_LIMIT;
	sf::Int64 updateWaitDelay = 1000000 / UPS_LIMIT;
	int frames = 0;

	//Haupt-Loop
	while (sceneManager.getGameWindow().isOpen())
	{
		//Updaten des Fensters
		if (updateClock.getElapsedTime().asMicroseconds() >= updateWaitDelay)
		{
			sf::Time deltaTime = updateClock.restart();

			sceneManager.checkWindowEvents();
			sceneManager.updateActivScene(deltaTime / 10.f);
		}

		//Zeichnen des Fensters
		if (drawClock.getElapsedTime().asMicroseconds() >= drawWaitDelay)
		{
			drawClock.restart();
			sceneManager.drawActivScene();

			frames++;
		}

		if (fpsClock.getElapsedTime().asMicroseconds() > 1000000) {
			fpsClock.restart();
			sceneManager.setDisplayFPS(frames);
			frames = 0;
		}
	}

	return EXIT_SUCCESS;
}

#ifndef NDEBUG
int main() {
	return mainLoop();
}
#else
int WinMain() {
	return mainLoop();
}
#endif

