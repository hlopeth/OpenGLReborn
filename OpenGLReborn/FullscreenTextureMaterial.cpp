#include "FullscreenTextureMaterial.h"
#include <glm/mat3x3.hpp>

const glm::mat3 filterLeft = glm::mat3(
	0.4155, -0.0458, -0.0545,
	0.4710, -0.0484, -0.0614,
	0.1670, -0.0258, 0.0128
);

const glm::mat3 filterRight = glm::mat3(
	-0.0109, 0.3756, -0.0651,
	-0.0365, 0.7333, -0.1286,
	-0.0060, 0.0111, 1.2968
);

FullscreenTextureMaterial::FullscreenTextureMaterial(GLTexture _textureLeft, GLTexture _textureRight):
	textureLeft(_textureLeft),
	textureRight(_textureRight),
	shader("screenVertex.glsl", "screenFragment.glsl")
{
}

void FullscreenTextureMaterial::draw(const Model& model, const RenderData& rd) const
{
	shader.use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureLeft.getID());
	shader.setUniform("screenTextureLeft", 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureRight.getID());
	shader.setUniform("screenTextureRight", 1);

	shader.setUniform("filterLeft", filterLeft);
	shader.setUniform("filterRight", filterRight);

	glBindVertexArray(model.getMesh()->getVAO());
	glDrawElements(GL_TRIANGLES, model.getMesh()->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
