#include "BoxMaterial.h"

BoxMaterial::BoxMaterial(glm::vec3 _color):
	color(_color),
	shaderProgram("BoxVertex.glsl", "BoxFragment.glsl")
{
}

void BoxMaterial::draw(Model& model, const RenderData& renderData)
{
	shaderProgram.use();
	auto modelMat = model.getModelMatrix();
	auto mvp = renderData.camera.getViewProjection() * modelMat;
	shaderProgram.setUniform("model", modelMat);
	shaderProgram.setUniform("mvp", mvp);
	shaderProgram.setUniform("color", color);

	glBindVertexArray(model.getMesh()->getVAO());
	glDrawElements(GL_TRIANGLES, model.getMesh()->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


