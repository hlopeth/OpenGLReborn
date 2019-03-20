#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
	Material()
	{
		ambient  = vec3(0.0f);
		diffuse  = vec3(0.0f);
		specular = vec3(0.0f);
		shininess = 0;
	}
	Material(vec3 ambient, vec3 diffuse, vec3 specular, float shininess)
	{
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->shininess = shininess;
		this->specular = specular;
	}
};