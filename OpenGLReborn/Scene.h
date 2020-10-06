#pragma once
#include <vector>
#include "GameObject.h"
#include "PointLight.h"
#include "SkyBox.h"
#include "DirectinalLight.h"

#define MAX_POINT_LIGHTS 16

using std::vector;

class Scene
{
public:
	vector<GameObject*>& getGameObjects();
	vector<PointLight*>& getPointLights();
	void addGameObject(GameObject* gameObject);
	bool addPointLight(PointLight* pointLight);
	void setSkyBox(SkyBox* skyBox);
	SkyBox* getSkyBox();
	void setDirectinalLight(DirectinalLight* directinalLight);
	DirectinalLight* getDirectinalLight();

	//DirectinalLight* directinalLight;
private:
	SkyBox* skyBox = nullptr;
	DirectinalLight* directinalLight;
	vector<GameObject*> gameObjects;
	vector<PointLight*> pointLights;
};