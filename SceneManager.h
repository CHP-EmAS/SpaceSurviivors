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

	void setWindowMode(bool border, bool fullscreen);
	void updateWindowSize();
	void setDisplayFPS(int fps);

	void fadeOut(sf::Color fadeColor = sf::Color::Black);
	void fadeIn(sf::Color fadeColor = sf::Color::Black);

	sf::RenderWindow& getGameWindow();

	Scene* getLastScene();
	Scene* getActivScene();
	Scene* getScene(Scene::SceneNames sceneType);

	bool debugShowHitboxes();
	bool debugShowVelocity();
	bool debugShowSpatialGrid();

	~SceneManager(void);
private:
	//Scenes
	Scene* activScene;

	Scene* allScenes[SCENE_AMOUNT];
	Scene::SceneNames secureCloseScene;

	//Debug
	bool showFPS;
	bool showHitboxes;
	bool showVelocity;
	bool showSpatialGrid;
	bool zoomOut;

	//Window
	sf::RenderWindow* gameWindow;
	sf::Image windowIcon;
	sf::View windowView;

	bool fullscreen;
	bool border;

	//fade
	sf::Clock fadeClock;
	int fadeAlpha;
	sf::RectangleShape fadeRectangle;

	//fps
	sf::Text fpsText;
};

