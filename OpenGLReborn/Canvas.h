#pragma once
#include "UIWiget.h"

namespace UI
{
	class Canvas : public UIWiget
	{
	public:

		int getMaxChildren() override;
		void draw(const Rect& renderArea) override;
	private:
		int maxChildren = 100;
	};
}