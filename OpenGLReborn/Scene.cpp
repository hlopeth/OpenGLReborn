#include "Scene.h"

vector<GameObject*>& Scene::getGameObjects()
{
	return gameObjects;
}

vector<PointLight*>& Scene::getPointLights()
{
	return pointLights;
}

void Scene::addGameObject(GameObject* gameObject)
{
	gameObjects.push_back(gameObject);
}

bool Scene::addPointLight(PointLight* pointLight)
{
	if (pointLights.size() >= MAX_POINT_LIGHTS)
	{
		return false;
	}

	pointLights.push_back(pointLight);

	return true;
}
