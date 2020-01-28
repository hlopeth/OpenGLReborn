#pragma once
#include "Scene.h"
#include "Camera.h"
#include "UIRoot.h"
#include "EventHandler.h"

class Level: EventHandler
{
public:
	Level();
	void update();
	Camera& getCamera();
	Scene& getScene();
	UIRoot& getUIRoot();
	void call(Event& event) override;
private:
	Camera camera;
	Scene scene;
	UIRoot uiRoot;
	double time = 0;
};