#include "GLTexture.h"
#include "TextureFromFile.h"
#include "Trace.h"

GLTexture::GLTexture(
	Texture texture,
	GLint _format, 
	GLint wrapS,
	GLint wrapT,
	GLint minFilter, 
	GLint magFilter,
	bool useMipMaps
) {
	format = _format;
	init(texture, wrapS, wrapT, minFilter, magFilter);
}

GLTexture::GLTexture(
	const char* path, 
	const std::string& directory,
	int _format, 
	bool useMipMaps
) {
	Texture texture = TextureFromFile(path, directory);
	format = _format;
	init(texture);
	delete[] texture.data;
}

void GLTexture::upload(Texture t)
{
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, format, t.width, t.height, 0, format, GL_UNSIGNED_BYTE, t.data);
}

void GLTexture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}

GLuint GLTexture::getID() const
{
	return id;
}

void GLTexture::unload()
{
	glDeleteTextures(1, &id);
}

GLTexture::~GLTexture()
{
}

void checkGLErrors1()
{
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		switch (err)
		{
		case GL_INVALID_ENUM:
			trace("GL_INVALID_ENUM");
			break;
		case GL_INVALID_VALUE:
			trace("GL_INVALID_ENUM");
			break;
		case GL_INVALID_OPERATION:
			trace("GL_INVALID_OPERATION");
			break;
		case GL_STACK_OVERFLOW:
			trace("GL_STACK_OVERFLOW");
			break;
		case GL_STACK_UNDERFLOW:
			trace("GL_STACK_UNDERFLOW");
			break;
		case GL_OUT_OF_MEMORY:
			trace("GL_OUT_OF_MEMORY");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			trace("GL_INVALID_FRAMEBUFFER_OPERATION");
			break;
		case GL_CONTEXT_LOST:
			trace("GL_CONTEXT_LOST");
			break;
		default:
			trace("GL_UNNOWN_ERROR");
			break;
		}
	}
}

void GLTexture::init(
	Texture texture, 
	GLint wrapS, 
	GLint wrapT, 
	GLint minFilter, 
	GLint magFilter,
	bool useMipMaps,
	bool useAnisotropicFiltering
) {
	glGenTextures(1, &id);
	bind();
	upload(texture);
	if (useMipMaps)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	checkGLErrors1();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	checkGLErrors1();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	checkGLErrors1();
	if (useAnisotropicFiltering && GLAD_GL_EXT_texture_filter_anisotropic) {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, 5.0f);
	}
}
