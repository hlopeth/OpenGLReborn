#pragma once
#include "UIWiget.h"

namespace UI
{
	class Button : public UIWiget
	{
	public:
		Button();
		int getMaxChildren() override;
		void draw() const override;
	};
}