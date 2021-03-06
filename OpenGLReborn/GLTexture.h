#pragma once
#include <string>
#include <glad/glad.h>
#include "Texture.h"

class TextureRenderTarget;

//������������� �������� � �����������, �� ������ ������ � ����������� ��������
class GLTexture {
public:
	GLTexture()
	{
		id = -1;
	}
	GLTexture(
		Texture texture,
		GLint format = GL_RGBA,
		GLint wrapS = GL_REPEAT,
		GLint wrapT = GL_REPEAT,
		GLint minFilter = GL_LINEAR,
		GLint magFilter = GL_LINEAR,
		bool useMipMaps = true
	);
	GLTexture(
		const char* path, 
		const std::string& directory,
		int format = GL_RGBA,
		bool useMipMaps = true
	);
	void allocate(size_t width, size_t height);
	void upload(Texture texture);
	void bind() const;
	GLuint getID() const;
	void unload();
	~GLTexture();
protected:
	GLint format;
	GLuint id;
private:
	void init(
		Texture* texture,
		GLint format,
		GLint wrapS = GL_REPEAT,
		GLint wrapT = GL_REPEAT,
		GLint minFilter = GL_LINEAR,
		GLint magFilter = GL_LINEAR,
		bool useMipMaps = true,
		bool useAnisotropicFiltering = true
	);
	friend TextureRenderTarget;
};