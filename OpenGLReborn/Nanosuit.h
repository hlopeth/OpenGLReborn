#pragma once
#include "GameObject.h"
#include "ModelComponent.h"

class Nanosuit : public GameObject
{
public:
	Nanosuit();
	const std::vector<Model>& getModel() const;
	void draw(RenderData& renderData) override;
private:
	std::vector<Model> models;
};