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

void Nanosuit::draw(Camera& camera)
{
	shaderProgram.use();
	shaderProgram.setUniform("mvp", camera.getViewProjection()*getModelMatrix());
	shaderProgram.setUniform("model", getModelMatrix());
	shaderProgram.setUniform("cameraPos", camera.Pos);
	model.Draw(shaderProgram);
}

void Nanosuit::setModel(Model& model)
{
	this->model = model;
}
