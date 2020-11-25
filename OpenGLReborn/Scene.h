#pragma once
#include <vector>
#include "GameObject.h"
#include "PointLight.h"
#include "SkyBox.h"
#include "DirectionalLight.h"

#define MAX_POINT_LIGHTS 16

using std::vector;

class Scene
{
public:
	vector<GameObject*>& getGameObjects();
	const vector<GameObject*>& getGameObjects() const;
	vector<PointLight*>& getPointLights();
	const vector<PointLight*>& getPointLights() const;
	void addGameObject(GameObject* gameObject);
	bool addPointLight(PointLight* pointLight);
	void setSkyBox(SkyBox* skyBox);
	const SkyBox* getSkyBox() const;
	void setDirectionalLight(DirectionalLight* directionalLight);
	const DirectionalLight* getDirectionalLight() const;

	//DirectionalLight* directionalLight;
private:
	SkyBox* skyBox = nullptr;
	DirectionalLight* directionalLight;
	vector<GameObject*> gameObjects;
	vector<PointLight*> pointLights;
};