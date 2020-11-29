#pragma once
#include "GameObject.h"
#include "PointLight.h"
#include "Box.h"

class Lamp : public GameObject
{
public:
	Lamp();
	PointLight pointLight;
	void setPosition(const vec3 position) override;
	virtual void draw(RenderData& renderData) const override;
private:
	Box box;
};