#include "TerrainMaterial.h"

TerrainMaterial::TerrainMaterial(GLTexture _diffuseTexture):
	diffuseTexture(_diffuseTexture),
	shader("terrainVertex.glsl", "terrainFragment.glsl")
{
}

void TerrainMaterial::draw(Model& model, const RenderData& renderData)
{
	shader.use();
	glm::mat4 modelMat = model.getModelMatrix();
	shader.setUniform("model", modelMat);
	shader.setUniform("mvp", renderData.camera.getViewProjection() * modelMat);

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
	glBindTexture(GL_TEXTURE_2D, diffuseTexture.getID());
	shader.setUniform("material.texture_diffuse1", 0);

	glBindVertexArray(model.getMesh()->getVAO());
	glDrawElements(GL_TRIANGLES, model.getMesh()->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
