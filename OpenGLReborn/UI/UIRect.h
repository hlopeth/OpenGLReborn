#pragma once
#include "UIWiget.h"

namespace UI
{
	using glm::vec4;
	class UIRect : public UIWiget
	{
	public:
		UIRect();
		UIRect(vec4 _color);
		~UIRect();
		int getMaxChildren() override;
		void draw() const override; 
		vec4 color;
	private:
		static GLuint VAO;
	};
}