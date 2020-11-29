#pragma once
#include "UIWiget.h"

namespace UI
{
	class VerticalLayout : public UIWiget
	{
	public:
		bool addChild(UIWiget* wiget) override;
		int getMaxChildren() override;
		void draw() const override;
		float spacing = 0;
	private:
		int maxChildren = 100;
		float nextChildrenY = 0;
	};
}
