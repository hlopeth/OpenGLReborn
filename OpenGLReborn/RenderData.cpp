#include "RenderData.h"

RenderData::RenderData(
	const Camera& _camera, 
	const vector<PointLight*>& _pointLights, 
	const DirectionalLight* _directionalLight
):
	camera(_camera), 
	pointLights(_pointLights),
	directionalLight(_directionalLight)
{
}
