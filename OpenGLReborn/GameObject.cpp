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
	modelMatrix = glm::translate(modelMatrix, position);
}

void GameObject::setScale(const vec3 scale)
{
	this->scale = scale;
	modelMatrix = glm::scale(modelMatrix, scale);
}

void GameObject::setRotation(const vec3 rotation)
{
	this->rotation = rotation;
	modelMatrix = glm::rotate(modelMatrix, rotation.x, vec3(1.0, 0.0, 0.0));
	modelMatrix = glm::rotate(modelMatrix, rotation.y, vec3(0.0, 1.0, 0.0));
	modelMatrix = glm::rotate(modelMatrix, rotation.z, vec3(0.0, 0.0, 1.0));
}

mat4 GameObject::getModelMatrix()
{
	return modelMatrix;
}
