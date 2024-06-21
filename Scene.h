#pragma once

#include "SFML/Graphics.hpp"

#define SCENE_AMOUNT 5

class Scene
{
public:
	enum SceneNames
	{
		Main_Menue,
		Game,
		Pause,
		GameOver,
		Level_UP,
		Stats,
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
	bool isLoaded;
	SceneNames sceneName;
	Scene* sceneBeforThis;
};

