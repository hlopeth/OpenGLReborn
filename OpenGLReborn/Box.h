#pragma once
#include "Model.h"

class Box : public Model
{
public:
	Box(shared_ptr<ModelMaterial> material);
};
