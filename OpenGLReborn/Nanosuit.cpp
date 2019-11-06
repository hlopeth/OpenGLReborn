#include "Nanosuit.h"
#include "Trace.h"

Nanosuit::Nanosuit(): 
	model(pathToModel.c_str())
{}

Model& Nanosuit::getModel()
{
	return model;
}

void Nanosuit::draw(Camera& camera)
{
	trace("Nanosuit::draw");
}

void Nanosuit::setModel(Model& model)
{
	this->model = model;
}
