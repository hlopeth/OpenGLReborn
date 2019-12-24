#pragma once
#include "GameObject.h"
#include "ModelComponent.h"

class Nanosuit : public GameObject, ModelComponent
{
public:
	Nanosuit();
	Model& getModel() override;
	void draw(Camera& camera) override;
private:
	void setModel(Model& model) override;
	Model model;
	ShaderProgram shaderProgram;
};