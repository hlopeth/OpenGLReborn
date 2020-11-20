#pragma once
#include <vector>
#include "Camera.h"
#include "PointLight.h"
#include "DirectinalLight.h"

using std::vector;

struct RenderData
{
	RenderData(
		const Camera& camera,
		const vector<PointLight*>& pointLights, 
		const DirectinalLight* dirextinalLight
	);
	const Camera& camera;
	const vector<PointLight*>& pointLights;
	const DirectinalLight* dirextinalLight;
};
