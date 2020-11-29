#pragma once
#include <memory>
#include "GameObject.h"
#include "Mesh.h"
#include "Material/AbstractMaterial.h"

class Model;

class ModelMaterial : public AbstractMaterial
{
public:
	virtual void draw(const Model& model, const RenderData& rd) const = 0;
};


class Model: public GameObject
{
public:
	Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<ModelMaterial> material);
	void draw(RenderData& rd) const override;
	std::shared_ptr<Mesh> getMesh() const;
	std::shared_ptr<ModelMaterial> getMaterial() const;
	void setMesh(std::shared_ptr<Mesh> mesh);
	void setMaterial(std::shared_ptr<ModelMaterial> material);
protected:
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<ModelMaterial> material;
};

