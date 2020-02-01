#include "Nanosuit.h"
#include "Trace.h"

#define PATH_TO_MODEL "assets/nanosuit/nanosuit.obj"
#define VERTEX_SHADER "NanosuitVertex.glsl"
#define FRAGMENT_SHADER "NanosuitFragment.glsl"

Nanosuit::Nanosuit(): 
	model(PATH_TO_MODEL),
	shaderProgram(VERTEX_SHADER, FRAGMENT_SHADER)
{}

Model& Nanosuit::getModel()
{
	return model;
}

void Nanosuit::draw(RenderData& rd)
{
	shaderProgram.use();
	shaderProgram.setUniform("mvp", rd.camera.getViewProjection()*getModelMatrix());
	PointLight* pointLight = nullptr;
	for (unsigned int i = 0; i < rd.pointLights.size(); i++)
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
	shaderProgram.setUniform("model", getModelMatrix());
	shaderProgram.setUniform("cameraPos", rd.camera.Pos);
	model.Draw(shaderProgram);
}

void Nanosuit::setModel(Model& model)
{
	this->model = model;
}
