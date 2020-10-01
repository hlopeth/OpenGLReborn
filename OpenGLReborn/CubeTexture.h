#pragma once
#include <glad/glad.h>
#include "Texture.h"

class CubeTexture {
public:
	CubeTexture();
	CubeTexture(
		Texture leftPath,
		Texture rightPath,
		Texture topPath,
		Texture bottomPath,
		Texture frontPath,
		Texture backPath
	);
	void bind() const;
	GLuint getId() const;
protected:
	GLuint id;
};