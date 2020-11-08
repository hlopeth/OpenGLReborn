#include "TerrainMaterial.h"

TerrainMaterial::TerrainMaterial(GLTexture _sandTexture, GLTexture _grassTexture, GLTexture _rockTexture):
	sandTexture(_sandTexture),
	grassTexture(_grassTexture),
	rockTexture(_rockTexture),
	shader("terrainVertex.glsl", "terrainFragment.glsl")
{
}

void TerrainMaterial::draw(GLuint vao, int indicesSize, const glm::mat4& modelMatrix, const RenderData& renderData)
{
	shader.use();
	shader.setUniform("model", modelMatrix);
	shader.setUniform("mvp", renderData.camera.getViewProjection() * modelMatrix);

	shader.setUniform("cameraPos", renderData.camera.pos);
	PointLight* pointLight = nullptr;
	int pointLightsSize = renderData.pointLights.size();
	shader.setUniform("n_pointLights", pointLightsSize);
	for (unsigned int i = 0; i < pointLightsSize; i++)
	{
		pointLight = renderData.pointLights[i];
		char ch_i = '0' + i;
		shader.setUniform(string("pointLights[") + ch_i + "].position", pointLight->position);
		shader.setUniform(string("pointLights[") + ch_i + "].ambient", pointLight->ambient);
		shader.setUniform(string("pointLights[") + ch_i + "].diffuse", pointLight->diffuse);
		shader.setUniform(string("pointLights[") + ch_i + "].specular", pointLight->specular);
		shader.setUniform(string("pointLights[") + ch_i + "].constant", pointLight->constant);
		shader.setUniform(string("pointLights[") + ch_i + "].linear", pointLight->linear);
		shader.setUniform(string("pointLights[") + ch_i + "].quadratic", pointLight->quadratic);
		shader.setUniform(string("pointLights[") + ch_i + "].farPlane", pointLight->farPlane);
	}

	shader.setUniform("directinalLight.direction", renderData.dirextinalLight->direction);
	shader.setUniform("directinalLight.color", renderData.dirextinalLight->color);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sandTexture.getID());
	shader.setUniform("sandMaterial.texture_diffuse1", 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, grassTexture.getID());
	shader.setUniform("grassMaterial.texture_diffuse1", 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, rockTexture.getID());
	shader.setUniform("rockMaterial.texture_diffuse1", 2);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
