#pragma once
#include "Mesh.h"

namespace RenderingPrimitives
{
	Mesh Box(vector<GLTexture> textures, glm::vec3 color);
	Mesh Plane(vector<GLTexture> textures, glm::vec3 color);
	GLTexture DefaultGLTexture();
}