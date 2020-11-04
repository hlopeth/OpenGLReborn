#include "Plane.h"
#include "MeshPrimitives.h"
#include "SingleTextureMaterial.h"

Plane::Plane(glm::vec3 color) :
	Model(
		make_shared<Mesh>(RenderingPrimitives::Plane()),
		make_shared<SingleTextureMaterial>(RenderingPrimitives::DefaultGLTexture(), color)
	)
{
}
