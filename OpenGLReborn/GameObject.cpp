#include "GameObject.h"

GameObject::GameObject() : 
	position(0.0), 
	scale(1.0), 
	rotation(0.0), 
	modelMatrix(1.0)
{}

vec3 GameObject::getPosition()
{
	return position;
}

vec3 GameObject::getScale()
{
	return scale;
}

vec3 GameObject::getRotation()
{
	return rotation;
}

void GameObject::setPosition(const vec3 position)
{
	this->position= position;
	modelMatrixIsDirty = true;
}

void GameObject::setScale(const vec3 scale)
{
	this->scale = scale;
	modelMatrixIsDirty = true;
}

void GameObject::setRotation(const vec3 rotation)
{
	this->rotation = rotation;
	modelMatrixIsDirty = true;
}

void GameObject::addChild(GameObject* child)
{
	childs.push_back(child);
	child->parent = this;
}

mat4 GameObject::getModelMatrix()
{
	if (modelMatrixIsDirty) {
		modelMatrix = mat4(1.0);
		modelMatrix = glm::rotate(modelMatrix, rotation.x, vec3(1.0, 0.0, 0.0));
		modelMatrix = glm::rotate(modelMatrix, rotation.y, vec3(0.0, 1.0, 0.0));
		modelMatrix = glm::rotate(modelMatrix, rotation.z, vec3(0.0, 0.0, 1.0));
		modelMatrix = glm::scale(modelMatrix, scale);
		modelMatrix = glm::translate(modelMatrix, position);
		modelMatrixIsDirty = false;
	}
	if (parent != nullptr) {
		return parent->getModelMatrix() * modelMatrix;
	}
	else {
		return modelMatrix;
	}
}
