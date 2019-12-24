#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "WindowManager.h"
#include "EventHandler.h"

using glm::vec3;
using glm::mat4;

class Camera: EventHandler
{
public:
	glm::vec3 Pos;
	glm::vec3 Front;
	glm::vec3 Up;
	
	Camera(vec3 _Pos, vec3 _Front, vec3 _Up);
	mat4 getView();
	mat4 getProjection();
	mat4 getViewProjection();
	vec3 Right();
	void call(Event& event) override;
private:
	glm::mat4 projection;
	float cameraYaw = -90.0f;
	float cameraPitch = 0.0f;
};