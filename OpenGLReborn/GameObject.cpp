#include "GameObject.h"

GameObject::GameObject() :
	position(0.0),
	scale(1.0),
	rotation(0.0),
	modelMatrix(1.0)
{
}

vec3 GameObject::getPosition() const
{
	return position;
}

vec3 GameObject::getScale() const
{
	return scale;
}

vec3 GameObject::getRotation() const
{
	return rotation;
}

void GameObject::setPosition(const vec3 position)
{
	this->position= position;
	if (usePhysics()) {
		physicsBody->setPosition(position);
	}
	modelMatrixIsDirty = true;
}

void GameObject::setScale(const vec3 scale)
{
	this->scale = scale;
	if (usePhysics()) {
		physicsBody->setScale(scale);
	}
	modelMatrixIsDirty = true;
}

void GameObject::setRotation(const vec3 rotation)
{
	this->rotation = rotation;
	if (usePhysics()) {
		physicsBody->setRotation(rotation);
	}
	modelMatrixIsDirty = true;
}

void GameObject::call(const Event& event)
{
	EventComponent::call(event);
	for (auto child : childs)
	{
		child->call(event);
	}
}

void GameObject::onPhysicsUpdate()
{
	if (usePhysics()) {
		copyTransform(*physicsBody);
	}
}

void GameObject::addChild(GameObject* child)
{
	childs.push_back(child);
	child->parent = this;
}

bool GameObject::usePhysics()
{
	return physicsBody != nullptr;
}

GameObject::~GameObject()
{
	delete physicsBody;
	physicsBody = nullptr;
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
