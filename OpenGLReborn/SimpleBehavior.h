#pragma once
#include "UIBehaviorComponent.h"

namespace UI 
{
	//Изменяет положение относительно родителя, но не изменяет размер
	class SimpleBehavior: public UIBehaviorComponent
	{
	public:
		SimpleBehavior(float x, float y, float width, float height);
		SimpleBehavior(Rect transform);
		Rect getTransform() override;
		Rect align(Rect parentTransform);
		Rect transform;
	};
}