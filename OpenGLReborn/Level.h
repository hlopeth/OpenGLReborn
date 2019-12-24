#pragma once
#include "Scene.h"
#include "Camera.h"
#include "EventHandler.h"

class Level: EventHandler
{
public:
	Level();
	void update();
	Camera& getCamera();
	Scene& getScene();
	void call(Event& event) override;
private:
	Camera camera;
	Scene scene;
};