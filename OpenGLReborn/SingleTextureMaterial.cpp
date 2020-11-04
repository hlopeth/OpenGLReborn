#include "SingleTextureMaterial.h"

SingleTextureMaterial::SingleTextureMaterial(
	GLTexture _diffuseTexture, 
	glm::vec3 _color
): 
	diffuseTexture(_diffuseTexture),
	color(_color),
	shader("TexturedVertex.glsl", "TexturedFragment.glsl")
{
}

void SingleTextureMaterial::draw(Model& model, const RenderData& rd)
{
	shader.use();

	auto modelMatrix = model.getModelMatrix();
	auto mvp = rd.camera.getViewProjection() * modelMatrix;
	shader.setUniform("mvp", mvp);
	shader.setUniform("model", modelMatrix);
	shader.setUniform("cameraPos", rd.camera.pos);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTexture.getID());
	shader.setUniform("material.texture_diffuse", GL_TEXTURE0);
	shader.setUniform("material.color", color);

	glBindVertexArray(model.getMesh()->getVAO());
	glDrawElements(GL_TRIANGLES, model.getMesh()->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
