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
		void draw(const Rect& renderArea) override;
		void align(Rect parentTransform) override;
		float spacing = 0;
	private:
		int maxChildren = 100;
	};
}
