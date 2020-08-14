#include "Transform3DComponent.h"

void Transform3DComponent::copyTransform(const Transform3DComponent& transform)
{
	setPosition(transform.getPosition());
	setScale(transform.getScale());
	setRotation(transform.getRotation());
}
