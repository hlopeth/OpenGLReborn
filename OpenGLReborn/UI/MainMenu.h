#pragma once
#include "Canvas.h"
#include "Button.h"
#include "Event/KeyEvent.h"
#include "Event/MouseClickEvent.h"

namespace UI
{
	class MainMenu : public Canvas
	{
	public:
		MainMenu();
		void draw() const override;
	private:
		vec4 backgroundColor = vec4(1.0);
		Button exitButton;
		void onKey(const KeyEvent& event);
		void exitButtonClick(const MouseLeftClickEvent&);
	};
}
