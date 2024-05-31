#include <SFML/Graphics.hpp>

#include <thread>

#include "Defines.h"

#include "Locator.h"
#include "SceneManager.h"
#include "GraphicLoader.h"

int main(int argc, char* argv[])
{
    bool debug = true;

    if (argc > 1)
    {
        if (std::string(argv[1]) == "-d")
        {
            debug = true;
        }
    }

    srand(time(NULL));

    if (!debug) //Konsolen-Fenster verstecken falls Debugmode aus
    {
        ShowWindow(GetConsoleWindow(), SW_HIDE);
    }

	GraphicLoader* graphicLoader = new GraphicLoader();
	Locator::provide(graphicLoader);
	graphicLoader->loadAllFonts();
	graphicLoader->loadAllGraphics();
	
	SceneManager* sceneManager = new SceneManager();
	Locator::provide(sceneManager);
	sceneManager->setWindowMode(true, true);
	sceneManager->initScenes();
	sceneManager->changeScene(Scene::Game, false);
	

	sf::Clock drawClock;
	sf::Clock updateClock;
	sf::Clock fpsClock;

	sf::Int64 drawWaitDelay = 1000000 / FPS_LIMIT;
	sf::Int64 updateWaitDelay = 1000000 / UPS_LIMIT;
	int frames = 0;

	//Haupt-Loop
	while (sceneManager->getGameWindow().isOpen())
	{
		//Updaten des Fensters
		if (updateClock.getElapsedTime().asMicroseconds() >= updateWaitDelay)
		{
			sf::Time deltaTime = updateClock.restart();

			sceneManager->checkWindowEvents();
			sceneManager->updateActivScene(deltaTime);
		}

		//Zeichnen des Fensters
		if (drawClock.getElapsedTime().asMicroseconds() >= drawWaitDelay)
		{
			drawClock.restart();
			sceneManager->drawActivScene();

			frames++;
		}

		if (fpsClock.getElapsedTime().asMicroseconds() > 1000000) {
			fpsClock.restart();
			sceneManager->setDisplayFPS(frames);
			frames = 0;
		}
	}

	sceneManager->deleteScenes();
	delete sceneManager;

	return EXIT_SUCCESS;
}

