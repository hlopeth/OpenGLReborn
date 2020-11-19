#include "WaterMaterial.h"

WaterMaterial::WaterMaterial(vec4 _color):
	color(_color),
	shader("waterVertex.glsl", "waterFragment.glsl")
{
}

void WaterMaterial::draw(const Model& model, const RenderData& rd) const
{
	shader.use();
	auto modelMat = model.getModelMatrix();
	auto mvp = rd.camera.getViewProjection() * modelMat;
	shader.setUniform("model", modelMat);
	shader.setUniform("mvp", mvp);
	shader.setUniform("color", color);
	shader.setUniform("time", time);


	shader.setUniform("directinalLight.direction", rd.dirextinalLight->direction);
	shader.setUniform("directinalLight.color", rd.dirextinalLight->color);
	shader.setUniform("cameraPos", rd.camera.pos);

	glBindVertexArray(model.getMesh()->getVAO());
	glDrawElements(GL_TRIANGLES, model.getMesh()->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
