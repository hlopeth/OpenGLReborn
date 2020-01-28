#pragma once
#include "Rect.h"

namespace UI
{
	class UIBehaviorComponent
	{
	public:
		virtual Rect getTransform() = 0;
	};
}