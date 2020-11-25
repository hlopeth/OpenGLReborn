#pragma once
#include <vector>
#include "Camera.h"
#include "PointLight.h"
#include "DirectionalLight.h"

using std::vector;

struct RenderData
{
	RenderData(
		const Camera& camera,
		const vector<PointLight*>& pointLights, 
		const DirectionalLight* directionalLight
	);
	const Camera& camera;
	const vector<PointLight*>& pointLights;
	const DirectionalLight* directionalLight;
};
