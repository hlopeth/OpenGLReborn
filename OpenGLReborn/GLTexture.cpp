#include "GLTexture.h"
#include "TextureFromFile.h"

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
	_format = GL_RGBA;
	init(texture);
	delete[] texture.data;
}

void GLTexture::upload(Texture t)
{
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, format, t.width, t.height, 0, format, GL_UNSIGNED_BYTE, t.data);
	glGenerateMipmap(GL_TEXTURE_2D);
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
	Texture texture, 
	GLint wrapS, 
	GLint wrapT, 
	GLint minFilter, 
	GLint magFilter,
	bool useMipMaps
) {
	glGenTextures(1, &id);
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	if (useMipMaps) 
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	upload(texture);
}
