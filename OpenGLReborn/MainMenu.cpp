#include "MainMenu.h"
#include "VerticalLayout.h"
#include "WindowManager.h"
#include "ExitEvent.h"
#include "LevelManager.h"
#include "UIRect.h"
#include "KeyEvent.h"
#include "Trace.h"

void UI::MainMenu::exitButtonClick(const MouseLeftClickEvent&) {
	ExitEvent exitEvent;
	LEVEL.call(exitEvent);
};

void UI::MainMenu::onKey(const KeyEvent& event) {
	if (event.key == GLFW_KEY_TAB && event.action == GLFW_PRESS) {
		visible = !visible;
	}
}

UI::MainMenu::MainMenu()
{
	this->setSize(WindowManager::windowWidth, WindowManager::windowHeight);

	VerticalLayout* layout = new VerticalLayout();
	vec2 layoutSize = vec2(WindowManager::windowWidth * 0.2, WindowManager::windowHeight * 0.8);
	vec2 layoutPosition = vec2(
		(WindowManager::windowWidth - layoutSize.x) / 2.0,
		(WindowManager::windowHeight - layoutSize.y) / 2.0
	);
	layout->setSize(layoutSize);
	layout->setPosition(layoutPosition);
	addChild(layout);

	exitButton.setEventHandler<MainMenu, MouseLeftClickEvent>(this, &MainMenu::exitButtonClick);
	exitButton.setSize(vec2(layoutSize.x, 100));
	layout->addChild(&exitButton);
	UIRect *rect = new UIRect(vec4(1.0, 0.0, 0.0, 1.0));
	rect->setSize(exitButton.getSize());
	exitButton.addChild(rect);
	this->setEventHandler<MainMenu, KeyEvent>(this, &MainMenu::onKey);

	UIRect* background = new UIRect(backgroundColor);
	background->setPosition(vec2(0.0, 0.0));
	background->setSize(WindowManager().windowWidth, WindowManager().windowHeight);
	addChild(background);
}

void UI::MainMenu::draw()
{
	drawChildren();
}