#include "Camera.h"
#include "MouseMoveEvent.h"
#include "Trace.h"

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
		MouseMoveEvent& me = (MouseMoveEvent&)event;
		cameraYaw += me.xOffset;
		cameraPitch += me.yOffset;

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
}