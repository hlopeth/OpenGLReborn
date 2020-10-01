#include "Box.h"
#include "MeshPrimitives.h"

Box::Box(glm::vec3 color): mesh(RenderingPrimitives::Box(vector<GLTexture>(), color))
{
	shader = ShaderProgram("BoxVertex.glsl", "BoxFragment.glsl");
}

void Box::draw(RenderData& renderData)
{
	shader.use();
	auto model = getModelMatrix();
	auto mvp = renderData.camera.getViewProjection() * model;
	shader.setUniform("model", model);
	shader.setUniform("mvp", mvp);
	mesh.Draw(shader);
}
