#include "SimpleBehavior.h"

UI::SimpleBehavior::SimpleBehavior(float x, float y, float width, float height) : transform(x, y, width, height)
{
}

UI::SimpleBehavior::SimpleBehavior(Rect _transform) : transform(_transform)
{
}

Rect UI::SimpleBehavior::getTransform()
{
	return transform;
}

Rect UI::SimpleBehavior::align(Rect parentTransform)
{
	transform.x += parentTransform.x;
	transform.y += parentTransform.y;
	return transform;
}
