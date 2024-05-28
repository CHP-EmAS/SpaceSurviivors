#pragma once

#include "SFML/Graphics.hpp"

#define SCENE_AMOUNT 7

class Scene
{
public:
	enum SceneNames
	{
		Main_Menue,
		Game,
		Pause,
		Stats,
		Options,
		Credits,
		Gameover,
		None
	};

	Scene(SceneNames scene);

	virtual void updateScene(sf::Time deltaTime) = 0;
	virtual void drawScene(sf::RenderWindow& mainWindow) = 0;

	virtual void checkEvents(sf::Event newEvent) = 0;

	virtual void loadScene() = 0;
	virtual void restartScene() = 0;
	virtual void closeScene() = 0;

	void setLastScene(Scene* lastScene);
	Scene* getLastScene();

	void setLoaded(bool load);
	bool isSceneLoaded();

	Scene::SceneNames getSceneName();

	virtual ~Scene(void);
protected:
	virtual void initScene() = 0;

	bool isLoaded;
	SceneNames sceneName;
	Scene* sceneBeforThis;
};

