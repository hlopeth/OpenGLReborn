#pragma once
#include <vector>
#include "Camera.h"
#include "PointLight.h"
#include "DirectinalLight.h"

using std::vector;

struct RenderData
{
	RenderData(Camera& camera, vector<PointLight*> pointLights, DirectinalLight* dirextinalLight);
	Camera& camera;
	vector<PointLight*> pointLights;
	DirectinalLight* dirextinalLight;
};
