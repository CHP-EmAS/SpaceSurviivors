#include "SceneManager.h"

#include <string>

#include "Scene.h"
#include "Game.h"
#include "GameOver.h"
#include "Pause.h"
#include "LevelUp.h"

#include "Locator.h"

SceneManager::SceneManager(void)
{
	gameWindow = nullptr;
	windowIcon.loadFromFile("img/asteroid.png");

	allScenes[Scene::Main_Menue] = nullptr;
	allScenes[Scene::Game] = nullptr;
	allScenes[Scene::Pause] = nullptr;
	allScenes[Scene::Level_UP] = nullptr;
	allScenes[Scene::GameOver] = nullptr;

	secureCloseScene = Scene::None;

	//fps
	fpsText.setString("XXX FPS");
	fpsText.setFillColor(sf::Color::Green);
	fpsText.setFont(Locator::get<GraphicService>()->getFont(GraphicService::Arial));
	fpsText.setCharacterSize(15);
	fpsText.setPosition(2, 0);

	//debug
	showFPS = false;
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
	allScenes[Scene::Pause] = new PauseScene();
	allScenes[Scene::Level_UP] = new LevelUpScene();
	allScenes[Scene::GameOver] = new GameOverScene();

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

	if (!(int(newScene) >= 0 && int(newScene) <= Scene::None))
	{
		return;
	}

	if (closeOldScene)
	{
		if (activScene != nullptr) 
			doSecureClose(activScene->getSceneName());
	}

	if (newScene != Scene::None)
	{
		allScenes[Scene::SceneNames(newScene)]->setLastScene(activScene);
		activScene = allScenes[Scene::SceneNames(newScene)];
	} else {
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
	if (!(int(scene) >= 0 && int(scene) < Scene::None))
	{
		return;
	}

	secureCloseScene = scene;
}

void SceneManager::drawActivScene()
{
	gameWindow->clear();

	//gameWindow->draw(background);

	activScene->drawScene(*gameWindow);

	if (showFPS) {
		gameWindow->draw(fpsText);
	}

	gameWindow->display();
}

void SceneManager::updateActivScene(const sf::Time& deltaTime)
{
	//Sicheres löschen
	if (secureCloseScene != Scene::None)
	{
		if (secureCloseScene != activScene->getSceneName())
		{
			if (getScene(secureCloseScene)->isSceneLoaded())
			{
				getScene(secureCloseScene)->closeScene();
				secureCloseScene = Scene::None;
			}
			else
			{
				secureCloseScene = Scene::None;
			}
		}
		else
		{
			secureCloseScene = Scene::None;
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
#if _DEBUG
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
				showFPS = !showFPS;
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
				zoomOut = !zoomOut;
				updateWindowSize();
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) {
				showSpatialGrid = !showSpatialGrid;
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) {
				showVelocity = !showVelocity;
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
				showHitboxes = !showHitboxes;
			} else 
#endif	
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F12)) {
				setWindowMode(true, !fullscreen);
			}
			break;
		case sf::Event::Resized:
			updateWindowSize();
			break;
		case sf::Event::JoystickConnected: {
			std::cout << "Connected" << std::endl;

			unsigned int buttonCount = sf::Joystick::getButtonCount(0);

			// check if joystick number 0 has a Z axis
			bool hasZ = sf::Joystick::hasAxis(0, sf::Joystick::Z);

			std::cout << buttonCount << " -> " << hasZ  << std::endl;
			break;
		}
		case sf::Event::JoystickDisconnected:
			std::cout << "Disconnected" << std::endl;
			break;
		case sf::Event::JoystickMoved:
			if(events.joystickMove.position > 20 || events.joystickMove.position < -20)
				std::cout << events.joystickMove.joystickId << ": " << events.joystickMove.axis << " -> " << events.joystickMove.position << std::endl;
			break;
		case sf::Event::JoystickButtonPressed:
			std::cout << events.joystickButton.joystickId << ": " << events.joystickButton.button << std::endl;
			break;
		}
	}
}

void SceneManager::setWindowMode(bool border, bool fullscreen)
{
	this->fullscreen = fullscreen;
	this->border = border;

	if (gameWindow == nullptr)
		gameWindow = new sf::RenderWindow;

	if (fullscreen)
	{
		gameWindow->create(sf::VideoMode::getFullscreenModes()[0], GAME_TITLE, sf::Style::Fullscreen);
	}
	else if (border)
	{
		gameWindow->create(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), GAME_TITLE, sf::Style::Default);
	}
	else
	{
		gameWindow->create(sf::VideoMode::getDesktopMode(), GAME_TITLE, sf::Style::None);
	}

	gameWindow->setIcon(windowIcon.getSize().x, windowIcon.getSize().y, windowIcon.getPixelsPtr());

	sf::Cursor cursor;
	if (cursor.loadFromSystem(sf::Cursor::Cross))
		gameWindow->setMouseCursor(cursor);

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
		windowView.setSize(WINDOW_SIZE + WINDOW_SIZE, WINDOW_SIZE + WINDOW_SIZE);
	}
	
	windowView.setViewport(sf::FloatRect(posPercentX, 0, percentX, 1));

	gameWindow->setView(windowView);
}

void SceneManager::setDisplayFPS(int fps)
{
	fpsText.setString(std::to_string(fps) + " FPS");
}

void SceneManager::setBackgorundReferencePoint(sf::Vector2f point)
{
	background.update(point);
}

sf::RenderWindow& SceneManager::getGameWindow()
{
	return *gameWindow;
}

sf::Vector2f SceneManager::getMousePosition()
{
	sf::Vector2i mouseWindowPosition = sf::Mouse::getPosition(*gameWindow);
	return gameWindow->mapPixelToCoords(mouseWindowPosition);
}

Scene* SceneManager::getLastScene()
{
	return activScene->getLastScene();
}

Scene* SceneManager::getActivScene()
{
	return activScene;
}

Scene* SceneManager::getScene(Scene::SceneNames scene)  const
{
	if (int(scene) >= 0 && int(scene) < (int)Scene::None)
	{
		return allScenes[scene];
	}
	else
	{
		return allScenes[Scene::Main_Menue];
	}
}

bool SceneManager::debugShowHitboxes() const
{
	return showHitboxes;
}

bool SceneManager::debugShowVelocity() const
{
	return showVelocity;
}

bool SceneManager::debugShowSpatialGrid() const
{
	return showSpatialGrid;
}

SceneManager::~SceneManager(void)
{
	deleteScenes();
	delete gameWindow;
}
