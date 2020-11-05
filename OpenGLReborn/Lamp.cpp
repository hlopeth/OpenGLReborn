#include "Lamp.h"
#include "UnitColorMaterial.h"

Lamp::Lamp(): 
	box(make_shared<UnitColorMaterial>( vec3(0.5) )),
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
	dynamic_pointer_cast<UnitColorMaterial>(box.getMaterial())->color = pointLight.diffuse;
	box.draw(renderData);
}
			