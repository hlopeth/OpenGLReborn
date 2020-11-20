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
	const vector<GameObject*>& getGameObjects() const;
	vector<PointLight*>& getPointLights();
	const vector<PointLight*>& getPointLights() const;
	void addGameObject(GameObject* gameObject);
	bool addPointLight(PointLight* pointLight);
	void setSkyBox(SkyBox* skyBox);
	const SkyBox* getSkyBox() const;
	void setDirectinalLight(DirectinalLight* directinalLight);
	const DirectinalLight* getDirectinalLight() const;

	//DirectinalLight* directinalLight;
private:
	SkyBox* skyBox = nullptr;
	DirectinalLight* directinalLight;
	vector<GameObject*> gameObjects;
	vector<PointLight*> pointLights;
};