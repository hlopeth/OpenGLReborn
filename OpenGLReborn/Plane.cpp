#include "Plane.h"
#include "MeshPrimitives.h"

Plane::Plane(glm::vec3 color) : mesh(RenderingPrimitives::Plane(vector<Texture> { RenderingPrimitives::DefaultTexture() }, color))
{
	shader = ShaderProgram("TexturedVertex.glsl", "TexturedFragment.glsl");
}

void Plane::draw(RenderData& renderData)
{
	shader.use();
	auto model = getModelMatrix();
	auto mvp = renderData.camera.getViewProjection() * model;
	shader.setUniform("model", model);
	shader.setUniform("mvp", mvp);
	mesh.Draw(shader);
}
