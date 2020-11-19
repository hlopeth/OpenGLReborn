#pragma once
#include <memory>
#include "GameObject.h"
#include "Mesh.h"
#include "AbstractMaterial.h"

class Model;

class ModelMaterial : public AbstractMaterial
{
public:
	virtual void draw(const Model& model, const RenderData& rd) const = 0;
};


class Model: public GameObject
{
public:
	Model(shared_ptr<Mesh> mesh, shared_ptr<ModelMaterial> material);
	void draw(RenderData& rd) const override;
	shared_ptr<Mesh> getMesh() const;
	shared_ptr<ModelMaterial> getMaterial() const;
	void setMesh(shared_ptr<Mesh> mesh);
	void setMaterial(shared_ptr<ModelMaterial> material);
protected:
	shared_ptr<Mesh> mesh;
	shared_ptr<ModelMaterial> material;
};

