#include "Box.h"
#include "MeshPrimitives.h"

Box::Box(shared_ptr<ModelMaterial> material): Model(make_shared<Mesh>(RenderingPrimitives::Box()), material)
{
}
