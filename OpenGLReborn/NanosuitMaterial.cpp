#include "NanosuitMaterial.h"

#define VERTEX_SHADER "NanosuitVertex.glsl"
#define FRAGMENT_SHADER "NanosuitFragment.glsl"

NanosuitMaterial::NanosuitMaterial(
	GLTexture _diffuseTexture, 
	GLTexture _specularTexture, 
	GLTexture _normalTexture, 
	glm::vec3 _color
):
	diffuseTexture(_diffuseTexture),
	specularTexture(_specularTexture),
	normalTexture(_normalTexture),
	color(_color),
	shaderProgram(VERTEX_SHADER, FRAGMENT_SHADER)
{
}

void NanosuitMaterial::draw(Model& model, const RenderData& rd)
{
	shaderProgram.use();
	auto modelMat = model.getModelMatrix();
	auto mvp = rd.camera.getViewProjection() * modelMat;
	shaderProgram.setUniform("mvp", mvp);
	shaderProgram.setUniform("model", modelMat);
	shaderProgram.setUniform("cameraPos", rd.camera.pos);
	PointLight* pointLight = nullptr;
	int pointLightsSize = rd.pointLights.size();
	shaderProgram.setUniform("n_pointLights", pointLightsSize);
	for (unsigned int i = 0; i < pointLightsSize; i++)
	{
		pointLight = rd.pointLights[i];
		char ch_i = '0' + i;
		shaderProgram.setUniform(string("pointLights[") + ch_i + "].position", pointLight->position);
		shaderProgram.setUniform(string("pointLights[") + ch_i + "].ambient", pointLight->ambient);
		shaderProgram.setUniform(string("pointLights[") + ch_i + "].diffuse", pointLight->diffuse);
		shaderProgram.setUniform(string("pointLights[") + ch_i + "].specular", pointLight->specular);
		shaderProgram.setUniform(string("pointLights[") + ch_i + "].constant", pointLight->constant);
		shaderProgram.setUniform(string("pointLights[") + ch_i + "].linear", pointLight->linear);
		shaderProgram.setUniform(string("pointLights[") + ch_i + "].quadratic", pointLight->quadratic);
		shaderProgram.setUniform(string("pointLights[") + ch_i + "].farPlane", pointLight->farPlane);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTexture.getID());
	shaderProgram.setUniform("material.texture_diffuse0", GL_TEXTURE0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularTexture.getID());
	shaderProgram.setUniform("material.texture_specular0", GL_TEXTURE1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, normalTexture.getID());
	shaderProgram.setUniform("material.texture_normal0", GL_TEXTURE2);

	shaderProgram.setUniform("material.color", color);

	glBindVertexArray(model.getMesh()->getVAO());
	glDrawElements(GL_TRIANGLES, model.getMesh()->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
