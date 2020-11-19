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
	init(&texture, _format, wrapS, wrapT, minFilter, magFilter);
}

GLTexture::GLTexture(
	const char* path, 
	const std::string& directory,
	int _format, 
	bool useMipMaps
) {
	Texture texture = TextureFromFile(path, directory);
	init(&texture, _format);
	delete[] texture.data;
}

void GLTexture::allocate(size_t width, size_t height)
{
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);
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

void GLTexture::init(
	Texture* texture,
	GLint _format,
	GLint wrapS, 
	GLint wrapT, 
	GLint minFilter, 
	GLint magFilter,
	bool useMipMaps,
	bool useAnisotropicFiltering
) {
	format = _format;
	glGenTextures(1, &id);
	bind();
	if (texture != nullptr) 
	{
		upload(*texture);
	}
	if (useMipMaps)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	if (useAnisotropicFiltering && GLAD_GL_EXT_texture_filter_anisotropic) {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, 5.0f);
	}
}
