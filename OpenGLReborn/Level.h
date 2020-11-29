#pragma once
#include "Scene.h"
#include "Camera.h"
#include "GameObjects/UIRoot.h"
#include "Components/EventComponent.h"
#include "Event/ExitEvent.h"
#include "GameObjects/Model.h"

class Level: public EventComponent
{
public:
	Level();
	void update(double gameTime, double deltaTime);
	Camera& getCamera();
	const Camera& getCamera() const;
	Scene& getScene();
	const Scene& getScene() const;
	const UIRoot& getUIRoot() const;
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