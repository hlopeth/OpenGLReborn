#include "Model.h"

Model::Model(shared_ptr<Mesh> _mesh, shared_ptr<ModelMaterial> _material)
{
	mesh = _mesh;
	material = _material;
}

void Model::draw(RenderData& rd) const
{
	material->draw(*this, rd);
}

shared_ptr<Mesh> Model::getMesh() const
{
	return mesh;
}

shared_ptr<ModelMaterial> Model::getMaterial() const
{
	return material;
}

void Model::setMesh(shared_ptr<Mesh> _mesh)
{
	mesh = mesh;
}

void Model::setMaterial(shared_ptr<ModelMaterial> _material)
{
	material = _material;
}
