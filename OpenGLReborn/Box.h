#pragma once
#include "Model.h"
#include "SelectableComponent.h"

class Box : public Model
{
public:
	Box(shared_ptr<ModelMaterial> material);
	void update(double gameTime, double deltaTime) override;
	SelectableComponent selectableComponent;
};
