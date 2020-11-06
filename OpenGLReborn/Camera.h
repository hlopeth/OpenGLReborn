#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "WindowManager.h"
#include "KeyEvent.h"
#include "MouseMoveEvent.h"
#include "MouseClickEvent.h"
#include "EventComponent.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

class Camera: public EventComponent
{
public:
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	float speed = 20.0;
	
	Camera(vec3 _Pos, vec3 _Front, vec3 _Up);
	mat4 getView();
	mat4 getProjection();
	mat4 getViewProjection();
	vec3 Right();
	void update(double time, double deltaTime);
private:
	void onMouse(const MouseMoveEvent& event);
	void onKey(const KeyEvent& event);
	void onRightClick(const MouseRightClickEvent& event);
	glm::mat4 projection;
	float cameraYaw = -90.0f;
	float cameraPitch = 0.0f;
	double deltaTime = 0;
	bool moveForvard = false;
	bool moveBackvard = false;
	bool moveLeft = false;
	bool moveRight = false;
	bool moveUp = false;
	bool moveDown = false;
	bool sprint = false;
};