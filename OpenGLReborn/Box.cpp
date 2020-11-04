#include "Box.h"
#include "MeshPrimitives.h"

Box::Box(glm::vec3 color): Model(
	make_shared<Mesh>(RenderingPrimitives::Box()), 
	std::dynamic_pointer_cast<ModelMaterial>(make_shared<BoxMaterial>(BoxMaterial(color))))
{
	boxMaterial = std::dynamic_pointer_cast<BoxMaterial>(material);
}

shared_ptr<BoxMaterial> Box::getMaterial() const
{
	return boxMaterial;
}
