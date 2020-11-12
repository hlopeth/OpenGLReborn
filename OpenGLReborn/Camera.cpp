#include "Camera.h"
#include "MouseClickEvent.h"
#include "Trace.h"

bool moveCamera = false;

Camera::Camera(vec3 _Pos, vec3 _Front, vec3 _Up) :
	pos(_Pos), 
	front(_Front), 
	up(_Up)
{
	float aspect = WindowManager::windowWidth / (float)WindowManager::windowHeight;
	float fov = 60.0;
	float near = 0.1;
	float far = 10000.0;
	projection = glm::perspective(glm::radians(fov), aspect, near, far);

	setEventHandler<Camera, MouseMoveEvent>(this, &Camera::onMouse);
	setEventHandler<Camera, KeyEvent>(this, &Camera::onKey);
	setEventHandler<Camera, MouseRightClickEvent>(this, &Camera::onRightClick);
}

mat4 Camera::getView()
{
	return lookAt(pos, pos + front, up);
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
	return glm::normalize(glm::cross(front, up));
}

void Camera::update(double time, double deltaTime)
{
	if (!moveCamera || locked)
		return;
	float cameraSpeed = speed * deltaTime;
	if (sprint) cameraSpeed *= 10;
	if (moveForvard)
	{
		pos += cameraSpeed * front;
	}
	if (moveBackvard)
	{
		pos -= cameraSpeed * front;
	}
	if (moveLeft)
	{
		pos -= cameraSpeed * Right();
	}
	if (moveRight)
	{
		pos += cameraSpeed * Right();
	}
	if (moveUp)
	{
		pos += cameraSpeed * up;
	}
	if (moveDown)
	{
		pos -= cameraSpeed * up;
	}
}

void Camera::lock()
{
	locked = true;
}

void Camera::free()
{
	locked = false;
}

void Camera::onMouse(const MouseMoveEvent& event)
{
	if (!moveCamera || locked)
		return;
	
	cameraYaw += event.xOffset;
	cameraPitch += event.yOffset;

	if (cameraPitch > 89.0f)
		cameraPitch = 89.0f;
	if (cameraPitch < -89.0f)
		cameraPitch = -89.0f;

	front.x = (float)(cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch)));
	front.y = (float)(sin(glm::radians(cameraPitch)));
	front.z = (float)(sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch)));
}

void Camera::onKey(const KeyEvent& event)
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
	case GLFW_KEY_Q:
		moveDown = pressed;
		break;
	case GLFW_KEY_E:
		moveUp = pressed;
		break;
	case  GLFW_KEY_LEFT_SHIFT:
		sprint = pressed;
		break;
	}
}

void Camera::onRightClick(const MouseRightClickEvent& event)
{
	moveCamera = event.pressed;
}
