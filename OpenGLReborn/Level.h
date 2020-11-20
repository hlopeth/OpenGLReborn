#pragma once
#include "Scene.h"
#include "Camera.h"
#include "UIRoot.h"
#include "EventComponent.h"
#include "ExitEvent.h"
#include "Model.h"

class Level: public EventComponent
{
public:
	Level();
	void update(double gameTime, double deltaTime);
	Camera& getCamera();
	Scene& getScene();
	UIRoot& getUIRoot();
	void afterPhysicsUpdate();
	void call(const Event& event) override;
	Model* selectedModel = nullptr;
private:
	Camera camera;
	Scene scene;
	UIRoot uiRoot;
	void onKey(const KeyEvent& event);
	void onExit(const ExitEvent& event);
};