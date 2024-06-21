#pragma once

#include "Defines.h"

#include "ParallaxBackground.h"
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

	void setBackgorundReferencePoint(sf::Vector2f point);

	sf::RenderWindow& getGameWindow();
	sf::Vector2f getMousePosition();

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

	Scene* allScenes[Scene::None];
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

	//Background
	ParallaxBackground background;

	//fps
	sf::Text fpsText;
};

