#pragma once
#include <vector>
#include "Camera.h"
#include "PointLight.h"

using std::vector;

struct RenderData
{
	RenderData(Camera& camera, vector<PointLight*> pointLights);
	Camera& camera;
	vector<PointLight*> pointLights;
};
