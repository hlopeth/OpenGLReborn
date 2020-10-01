#include "Plane.h"
#include "MeshPrimitives.h"
#include "Trace.h"

Plane::Plane(glm::vec3 color) :
	GameObject(),
	mesh(RenderingPrimitives::Plane(vector<GLTexture> { RenderingPrimitives::DefaultGLTexture() }, color))
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
