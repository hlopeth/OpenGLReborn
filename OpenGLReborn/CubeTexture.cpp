#include "TextureFromFile.h"
#include "CubeTexture.h"

CubeTexture::CubeTexture()
{
	id = -1;
}

CubeTexture::CubeTexture(
	Texture leftPath, 
	Texture rightPath, 
	Texture topPath, 
	Texture bottomPath, 
	Texture frontPath, 
	Texture backPath
) {
	Texture faces[] = { rightPath, leftPath, topPath, bottomPath, frontPath, backPath };

    unsigned int width;
    unsigned int height;
    unsigned char* data;
    glGenTextures(1, &id);
    bind();
    for (unsigned int i = 0; i < 6; i++)
    {
        Texture t = faces[i];
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, t.width, t.height, 0, GL_RGB, GL_UNSIGNED_BYTE, t.data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void CubeTexture::bind() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}

GLuint CubeTexture::getId() const
{
	return id;
}
