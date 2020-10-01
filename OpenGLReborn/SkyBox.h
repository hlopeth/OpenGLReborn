#pragma once
#include "DrawComponent.h"
#include "CubeTexture.h"
#include "Shader.h"

class SkyBox : public DrawComponent {
public:
	SkyBox(CubeTexture texture);
	void draw(RenderData& renderData) override;
private:
	ShaderProgram shader;
	CubeTexture texture;
	GLuint VAO;
    const static GLfloat vertices[];
};