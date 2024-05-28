#include "SceneManager.h"

#include <string>

#include "Scene.h"
#include "GameScene.h"

#include "Locator.h"

SceneManager::SceneManager(void)
{
	gameWindow = nullptr;

	windowIcon.loadFromFile("Img/ect/schwert.png");

	setWindowParameter(WINDOW_SIZE, WINDOW_SIZE, true, false);

	
	allScenes[Scene::Main_Menue] = nullptr;
	allScenes[Scene::Game] = nullptr;
	allScenes[Scene::Pause] = nullptr;
	allScenes[Scene::Stats] = nullptr;
	allScenes[Scene::Options] = nullptr;
	allScenes[Scene::Credits] = nullptr;
	allScenes[Scene::Gameover] = nullptr;

	secureCloseScene = Scene::None;

	//fading
	fadeAlpha = 0;
	fadeRectangle.setSize(sf::Vector2f(WINDOW_SIZE + 2, WINDOW_SIZE + 2));
	fadeRectangle.setPosition(-1, -1);
	fadeRectangle.setFillColor(sf::Color::Black);

	//fps
	fpsText.setString("XXX FPS");
	fpsText.setFillColor(sf::Color::Green);
	fpsText.setFont(Locator::getGraphicService().getFont(GraphicService::Arial));
	fpsText.setCharacterSize(15);
	fpsText.setPosition(2, 0);

	showHitboxes = false;
	showVelocity = false;
	showSpatialGrid = false;
	zoomOut = false;
}

void SceneManager::initScenes()
{
	deleteScenes();

	//allScenes[Scene::Main_Menue] = 
	allScenes[Scene::Game] = new GameScene();
	//allScenes[Scene::Pause] = nullptr;
	//allScenes[Scene::Stats] = nullptr;
	//allScenes[Scene::Options] = nullptr;
	//allScenes[Scene::Credits] = nullptr;
	//allScenes[Scene::Gameover] = nullptr;

	activScene = nullptr;
}

void SceneManager::deleteScenes()
{
	for (int i_scene = 0; i_scene < SCENE_AMOUNT; i_scene++)
	{
		if (allScenes[Scene::SceneNames(i_scene)] != nullptr)
		{
			allScenes[Scene::SceneNames(i_scene)]->closeScene();
			delete allScenes[Scene::SceneNames(i_scene)];
			allScenes[Scene::SceneNames(i_scene)] = nullptr;
		}
	}
}

void SceneManager::changeScene(Scene::SceneNames newScene, bool closeOldScene)
{

	if (!(int(newScene) >= 0 && int(newScene) <= SCENE_AMOUNT))
	{
		return;
	}

	if (closeOldScene)
	{
		if (activScene != nullptr) doSecureClose(activScene->getSceneName());
	}

	if (newScene != Scene::None)
	{
		allScenes[Scene::SceneNames(newScene)]->setLastScene(activScene);
		activScene = allScenes[Scene::SceneNames(newScene)];
	}
	else
	{
		activScene = nullptr;
	}

	if (activScene != nullptr)
	{
		if (!activScene->isSceneLoaded())
		{
			activScene->loadScene();
		}
	}
}

void SceneManager::doSecureClose(Scene::SceneNames scene)
{
	if (!(int(scene) >= 0 && int(scene) < SCENE_AMOUNT))
	{
		return;
	}

	secureCloseScene = scene;
}

void SceneManager::drawActivScene()
{
	gameWindow->clear();

	activScene->drawScene(*gameWindow);

	//draw fade Rectangle
	if (fadeAlpha > 0) {
		gameWindow->draw(fadeRectangle);
	}

	gameWindow->draw(fpsText);

	gameWindow->display();
}

void SceneManager::updateActivScene(sf::Time deltaTime)
{
	//Sicheres löschen
	if (secureCloseScene != Scene::SceneNames::None)
	{
		if (secureCloseScene != activScene->getSceneName())
		{
			if (getScene(secureCloseScene)->isSceneLoaded())
			{
				getScene(secureCloseScene)->closeScene();
				secureCloseScene = Scene::SceneNames::None;
			}
			else
			{
				secureCloseScene = Scene::SceneNames::None;
			}
		}
		else
		{
			secureCloseScene = Scene::SceneNames::None;
		}
	}

	//Update des Activen Scenes
	activScene->updateScene(deltaTime);
}

void SceneManager::checkWindowEvents()
{
	sf::Event events;

	while (gameWindow->pollEvent(events))
	{
		activScene->checkEvents(events);

		switch (events.type)
		{
		case sf::Event::Closed:
			gameWindow->close();
			break;
		case sf::Event::KeyPressed:
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
				zoomOut = !zoomOut;
				updateWindowSize();
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
				showSpatialGrid = !showSpatialGrid;
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) {
				showVelocity = !showVelocity;
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) {
				showHitboxes = !showHitboxes;
			}

			break;
		}
		case sf::Event::Resized:
		{
			updateWindowSize();
			break;
		}
		}
	}
}

void SceneManager::setWindowMode()
{
	if (gameWindow != nullptr)
		delete gameWindow;

	gameWindow = new sf::RenderWindow;

	if (fullscreen)
	{
		gameWindow->create(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), GAME_TITLE, sf::Style::Fullscreen);
	}
	else if (border)
	{
		gameWindow->create(sf::VideoMode(sizeX, sizeY), GAME_TITLE, sf::Style::Default);
		gameWindow->setSize(sf::Vector2u(sizeX, sizeY));
	}
	else
	{
		gameWindow->create(sf::VideoMode(sizeX, sizeY), GAME_TITLE, sf::Style::None);
		gameWindow->setSize(sf::Vector2u(sizeX, sizeY));
	}

	//gameWindow->setIcon(32, 32, windowIcon.getPixelsPtr());
	//gameWindow->setVerticalSyncEnabled(true);
	//gameWindow->setMouseCursorGrabbed(true);

	sf::Cursor cursor;
	if (cursor.loadFromSystem(sf::Cursor::Cross))
		gameWindow->setMouseCursor(cursor);

	windowHandle = gameWindow->getSystemHandle();

	updateWindowSize();
}

void SceneManager::updateWindowSize()
{
	float tempSizeX = gameWindow->getSize().x;
	float tempSizeY = gameWindow->getSize().y;

	float percentX = tempSizeY / tempSizeX;
	float posPercentX = ((tempSizeX - tempSizeY) / 2.f) / tempSizeX;

	windowView.setCenter(WINDOW_SIZE / 2, WINDOW_SIZE / 2);
	if (!zoomOut) {
		windowView.setSize(WINDOW_SIZE, WINDOW_SIZE);
	} else {
		windowView.setSize(WINDOW_SIZE + 300, WINDOW_SIZE + 300);
	}
	
	windowView.setViewport(sf::FloatRect(posPercentX, 0, percentX, 1));

	gameWindow->setView(windowView);
}

void SceneManager::setWindowParameter(int width, int height, bool border, bool fullscreen)
{
	this->sizeX = width;
	this->sizeY = height;
	this->border = border;
	this->fullscreen = fullscreen;

	setWindowMode();
}

void SceneManager::setDisplayFPS(int fps)
{
	fpsText.setString(std::to_string(fps) + " FPS");
}

void SceneManager::fadeOut(sf::Color fadeColor)
{
	fadeClock.restart();

	fadeColor.a = 0;
	fadeRectangle.setFillColor(fadeColor);

	while (fadeAlpha < 255)
	{
		if (fadeClock.getElapsedTime().asMilliseconds() > 1)
		{
			drawActivScene();

			fadeColor.a = ++fadeAlpha;
			fadeRectangle.setFillColor(fadeColor);

			fadeClock.restart();
		}
	}
}

void SceneManager::fadeIn(sf::Color fadeColor)
{
	fadeClock.restart();

	fadeColor.a = 255;
	fadeRectangle.setFillColor(fadeColor);

	while (fadeAlpha > 0)
	{
		if (fadeClock.getElapsedTime().asMilliseconds() > 1)
		{
			drawActivScene();

			fadeColor.a = --fadeAlpha;
			fadeRectangle.setFillColor(fadeColor);

			fadeClock.restart();
		}
	}
}

sf::RenderWindow& SceneManager::getGameWindow()
{
	return *gameWindow;
}

HWND& SceneManager::getGameWindowHandle()
{
	return windowHandle;
}

Scene* SceneManager::getLastScene()
{
	return activScene->getLastScene();
}

Scene* SceneManager::getActivScene()
{
	return activScene;
}

Scene* SceneManager::getScene(Scene::SceneNames scene)
{
	if (int(scene) >= 0 && int(scene) < SCENE_AMOUNT)
	{
		return allScenes[scene];
	}
	else
	{
		return allScenes[Scene::Main_Menue];
	}
}

bool SceneManager::debugShowHitboxes()
{
	return showHitboxes;
}

bool SceneManager::debugShowVelocity()
{
	return showVelocity;
}

bool SceneManager::debugShowSpatialGrid()
{
	return showSpatialGrid;
}

SceneManager::~SceneManager(void)
{
	deleteScenes();
}
