#include "Lamp.h"
#include "UnitColorMaterial.h"

Lamp::Lamp(): 
	box(make_shared<UnitColorMaterial>( vec4(0.5, 0.5, 0.5, 1.0) )),
	GameObject()
{
	addChild(&box);
	box.setScale(vec3(0.5));
}

void Lamp::setPosition(const vec3 position)
{
	GameObject::setPosition(position);
	pointLight.position = position;
}

void Lamp::draw(RenderData& renderData)
{
	dynamic_pointer_cast<UnitColorMaterial>(box.getMaterial())->color = vec4(pointLight.diffuse, 1.0);
	box.draw(renderData);
}
			