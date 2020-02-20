#pragma once
#include "Canvas.h"
#include "Button.h"
#include "KeyEvent.h"
#include "MouseClickEvent.h"

namespace UI
{
	class MainMenu : public Canvas
	{
	public:
		MainMenu();
		void draw() override;
	private:
		vec4 backgroundColor = vec4(1.0);
		Button exitButton;
		void onKey(const KeyEvent& event);
		void exitButtonClick(const MouseLeftClickEvent&);
	};
}
