#pragma once
#ifndef __gl_h_
#include <glad/glad.h>
#endif
#include "GLTexture.h"

class TextureRenderTarget 
{
public:
	TextureRenderTarget();
	TextureRenderTarget(size_t width, size_t height);
	~TextureRenderTarget();
	void allocate(size_t width, size_t height);
	void bind() const;
	bool isComplete() const;
	GLuint getFbo() const;
	GLuint getRbo() const;
	GLTexture getTexture() const;
private:
	GLuint fbo;
	//depth renderbuffer
	GLuint rbo;
	GLTexture texture;
};