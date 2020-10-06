#include "RenderData.h"

RenderData::RenderData(
	Camera& _camera, 
	vector<PointLight*> _pointLights, 
	DirectinalLight* _dirextinalLight
) : camera(_camera), pointLights(_pointLights), dirextinalLight(_dirextinalLight)
{
}
