#include "Scene.h"

Scene::Scene(Scene::SceneNames sceneName)
{
	this->sceneName = sceneName;
	isLoaded = false;
	Scene* sceneBeforThis = nullptr;
}

void Scene::setLastScene(Scene* lastScene)
{
	sceneBeforThis = lastScene;
}

Scene* Scene::getLastScene()
{
	return sceneBeforThis;
}

void Scene::setLoaded(bool load)
{
	isLoaded = load;
}

bool Scene::isSceneLoaded()
{
	return isLoaded;
}

Scene::SceneNames Scene::getSceneName()
{
	return sceneName;
}

Scene::~Scene(void)
{

}
