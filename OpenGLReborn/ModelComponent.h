#pragma once
#include "Model.h"

class ModelComponent
{
public:
	virtual Model& getModel() = 0;
	virtual void setModel(Model& model) = 0;
};