#pragma once
#include "GameObject.h"
#include "Components/ModelComponent.h"

class Nanosuit : public GameObject
{
public:
	Nanosuit();
	const std::vector<Model>& getModel() const;
	void draw(RenderData& renderData) const override;
private:
	std::vector<Model> models;
};