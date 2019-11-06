#pragma once
#include "Scene.h"
#include "Camera.h"

class Level
{
public:
	Level();
	void update();
	Camera& getCamera();
	Scene& getScene();
private:
	Camera camera;
	Scene scene;
};