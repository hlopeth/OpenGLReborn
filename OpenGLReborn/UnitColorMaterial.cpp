#include "UnitColorMaterial.h"

UnitColorMaterial::UnitColorMaterial(glm::vec4 _color):
	color(_color),
	shaderProgram("BoxVertex.glsl", "BoxFragment.glsl")
{
}

UnitColorMaterial::UnitColorMaterial(const UnitColorMaterial& material):
	UnitColorMaterial(material.color)
{

}

void UnitColorMaterial::draw(const Model& model, const RenderData& renderData) const
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


