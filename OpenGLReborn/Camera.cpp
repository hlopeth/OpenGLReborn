#include "Camera.h"
#include "MouseMoveEvent.h"
#include "Trace.h"
#include <iostream>

Camera::Camera(vec3 _Pos, vec3 _Front, vec3 _Up) :
	Pos(_Pos), 
	Front(_Front), 
	Up(_Up)
{
	float aspect = WindowManager::windowWidth / (float)WindowManager::windowHeight;
	float fov = 60.0;
	float near = 0.1;
	float far = 1000.0;
	projection = glm::perspective(glm::radians(fov), aspect, near, far);
}

mat4 Camera::getView()
{
	return lookAt(Pos, Pos + Front, Up);
}

mat4 Camera::getProjection()
{
	return projection;
}

mat4 Camera::getViewProjection()
{
	return projection * getView();
}

vec3 Camera::Right()
{
	return glm::normalize(glm::cross(Front, Up));
}

void Camera::call(Event& event)
{
	switch (event.getType())
	{
	case MOUSE_MOVE_EVENT:
	{
		MouseMoveEvent& me = (MouseMoveEvent&)event;
		cameraYaw += me.xOffset * 4;
		cameraPitch += me.yOffset * 4;

		if (cameraPitch > 89.0f)
			cameraPitch = 89.0f;
		if (cameraPitch < -89.0f)
			cameraPitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
		front.y = sin(glm::radians(cameraPitch));
		front.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
		Front = glm::normalize(front);
		break;
	}
	case KEY_EVENT:
		onKey((KeyEvent&)event);
		break;
	}
}

void Camera::update(double time, double deltaTime)
{
	float cameraSpeed = 10.0f * deltaTime;
	if (moveForvard)
	{
		Pos += cameraSpeed * Front;
	}
	if (moveBackvard)
	{
		Pos -= cameraSpeed * Front;
	}
	if (moveLeft)
	{
		Pos -= cameraSpeed * Right();
	}
	if (moveRight)
	{
		Pos += cameraSpeed * Right();
	}
	//std::cout << Pos.x << " " << Pos.y << " " << Pos.z << "\n";
}

void Camera::onKey(KeyEvent& event)
{
	bool pressed = event.action == GLFW_PRESS || event.action == GLFW_REPEAT;
	switch (event.key)
	{
	case GLFW_KEY_W:
	case GLFW_KEY_UP:
		moveForvard = pressed;
		break;
	case GLFW_KEY_S:
	case GLFW_KEY_DOWN:
		moveBackvard = pressed;
		break;
	case GLFW_KEY_D:
	case GLFW_KEY_RIGHT:
		moveRight = pressed;
		break;
	case GLFW_KEY_A:
	case GLFW_KEY_LEFT:
		moveLeft = pressed;
		break;
	}

}
