#pragma once

#include "Defines.h"

#include "Scene.h"

class SceneManager
{
public:
	SceneManager(void);

	void initScenes();
	void deleteScenes();

	void changeScene(Scene::SceneNames newScene, bool closeOldScene = true);
	void doSecureClose(Scene::SceneNames scene);

	void drawActivScene();
	void updateActivScene(sf::Time deltaTime);
	void checkWindowEvents();

	void setWindowMode();
	void updateWindowSize();
	void setWindowParameter(int width, int height, bool border, bool fullscreen);
	void setDisplayFPS(int fps);

	void fadeOut(sf::Color fadeColor = sf::Color::Black);
	void fadeIn(sf::Color fadeColor = sf::Color::Black);

	sf::RenderWindow& getGameWindow();
	HWND& getGameWindowHandle();

	Scene* getLastScene();
	Scene* getActivScene();
	Scene* getScene(Scene::SceneNames sceneType);

	bool debugDrawEnabled();

	~SceneManager(void);
private:
	//Scenes
	Scene* activScene;

	Scene* allScenes[SCENE_AMOUNT];
	Scene::SceneNames secureCloseScene;

	bool debugDraw;

	//Window
	sf::RenderWindow* gameWindow;
	sf::Image windowIcon;
	sf::View windowView;

	HWND windowHandle;

	int sizeX;
	int sizeY;
	bool fullscreen;
	bool border;

	//fade
	sf::Clock fadeClock;
	int fadeAlpha;
	sf::RectangleShape fadeRectangle;

	//fps
	sf::Text fpsText;
};

