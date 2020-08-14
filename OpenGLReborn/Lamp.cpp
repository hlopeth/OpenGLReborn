#include "Lamp.h"

Lamp::Lamp(): GameObject()
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
	box.mesh.color = pointLight.diffuse;
	box.draw(renderData);
}
			