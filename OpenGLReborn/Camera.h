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
	
	Camera(
		vec3 pos,
		vec3 front, 
		vec3 up,
		float near = 0.1f, 
		float far = 10000.f);
	Camera(vec3 pos, vec3 front, vec3 up, mat4 projection);
	mat4 getView() const;
	mat4 getProjection() const;
	mat4 getViewProjection() const;
	vec3 Right() const;
	float Near() const;
	float Far() const;
	void update(double time, double deltaTime);
	void lock();
	void free();

	const float fov = 60.0;
private:
	void onMouse(const MouseMoveEvent& event);
	void onKey(const KeyEvent& event);
	void onRightClick(const MouseRightClickEvent& event);
	glm::mat4 projection;
	float near;
	float far;
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
	bool locked = false;
};