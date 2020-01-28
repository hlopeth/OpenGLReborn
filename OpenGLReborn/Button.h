#pragma once
#include "UIWiget.h"

namespace UI
{
	class Button : public UIWiget
	{
	public:
		Button();
		void call(UIEvent& event) override;
		int getMaxChildren() override;
		void draw() override;
	};
}