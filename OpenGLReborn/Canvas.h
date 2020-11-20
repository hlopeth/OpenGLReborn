#pragma once
#include "UIWiget.h"

namespace UI
{
	class Canvas : public UIWiget
	{
	public:
		int getMaxChildren() override;
		void draw() const override;
	private:
		int maxChildren = 100;
	};
}