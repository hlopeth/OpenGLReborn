#include "RenderData.h"

RenderData::RenderData(
	const Camera& _camera, 
	const vector<PointLight*>& _pointLights, 
	const DirectinalLight* _dirextinalLight
):
	camera(_camera), 
	pointLights(_pointLights),
	dirextinalLight(_dirextinalLight)
{
}
