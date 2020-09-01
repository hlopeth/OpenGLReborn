#pragma once
#include "Scene.h"
#include "Camera.h"
#include "UIRoot.h"
#include "EventComponent.h"
#include "ExitEvent.h"

class Level: public EventComponent
{
public:
	Level();
	void update(double gameTime, double deltaTime);
	Camera& getCamera();
	Scene& getScene();
	UIRoot& getUIRoot();
	void onPhysicsUpdate();
	void call(const Event& event) override;
private:
	Camera camera;
	Scene scene;
	UIRoot uiRoot;
	double time = 0;
	void onKey(const KeyEvent& event);
	void onExit(const ExitEvent& event);
};