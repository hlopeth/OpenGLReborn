#pragma once
#include "UIWiget.h"

namespace UI
{
	class VerticalLayout : public UIWiget
	{
	public:
		bool addChild(UIWiget* wiget) override;
		int getMaxChildren() override;
		void call(UIEvent& event) override;
		void draw() override;
		float spacing = 0;
	private:
		int maxChildren = 100;
		float nextChildrenY = 0;
	};
}
