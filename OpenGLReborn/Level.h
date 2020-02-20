#pragma once
#include "Scene.h"
#include "Camera.h"
#include "UIRoot.h"
#include "EventComponent.h"

class Level: public EventComponent
{
public:
	Level();
	void update();
	Camera& getCamera();
	Scene& getScene();
	UIRoot& getUIRoot();
	void call(const Event& event) override;
private:
	Camera camera;
	Scene scene;
	UIRoot uiRoot;
	double time = 0;
	void onKey(const KeyEvent& event);
};