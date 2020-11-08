#pragma once
#include "Model.h"
#include "WaterMaterial.h"

class Water: public Model
{
public:
	Water(float width, float height, shared_ptr<WaterMaterial> material);

	void update(double gameTime, double deltaTime) override;

private:
	shared_ptr<Mesh> generateMesh(float width, float height);
};