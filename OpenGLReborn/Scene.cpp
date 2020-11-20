#include "Scene.h"

vector<GameObject*>& Scene::getGameObjects()
{
	return gameObjects;
}

const vector<GameObject*>& Scene::getGameObjects() const
{
	return gameObjects;
}

vector<PointLight*>& Scene::getPointLights()
{
	return pointLights;
}

const vector<PointLight*>& Scene::getPointLights() const
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

void Scene::setSkyBox(SkyBox* skyBox)
{
	this->skyBox = skyBox;
}

void Scene::setDirectinalLight(DirectinalLight* _directinalLight)
{
	directinalLight = _directinalLight;
}

const DirectinalLight* Scene::getDirectinalLight() const
{
	return directinalLight;
}

const SkyBox* Scene::getSkyBox() const
{
	return skyBox;
}
