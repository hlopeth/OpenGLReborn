#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

class Camera
{
public:
	glm::vec3 Pos;
	glm::vec3 Front;
	glm::vec3 Up;
	
	Camera()
	{
		Pos = vec3(0.0f);
		Front = vec3(0.0f, 0.0f, -1.0f);
		Up = vec3(0.0f, 1.0f, 0.0f);
	}

	Camera(vec3 _Pos, vec3 _Front, vec3 _Up) : Pos(_Pos), Front(_Front), Up(_Up)
	{}
	mat4 getMatrix()
	{
		return  lookAt(Pos, Pos + Front, Up);
	}
	vec3 Right()
	{
		return glm::normalize(glm::cross(Front, Up));
	}

};

