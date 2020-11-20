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

void GameObject::afterPhysicsUpdate()
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

void GameObject::update(double gameTime, double deltaTime)
{
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

const mat4 GameObject::getModelMatrix() const
{
	if (modelMatrixIsDirty) {
		//TODO теренести из const метода
		modelMatrix = mat4(1.0);
		modelMatrix = glm::translate(modelMatrix, position);
		modelMatrix = glm::rotate(modelMatrix, rotation.x, vec3(1.0, 0.0, 0.0));
		modelMatrix = glm::rotate(modelMatrix, rotation.y, vec3(0.0, 1.0, 0.0));
		modelMatrix = glm::rotate(modelMatrix, rotation.z, vec3(0.0, 0.0, 1.0));
		modelMatrix = glm::scale(modelMatrix, scale);
		modelMatrixIsDirty = false;
	}
	if (parent != nullptr) {
		return parent->getModelMatrix() * modelMatrix;
	}
	else {
		return modelMatrix;
	}
}
