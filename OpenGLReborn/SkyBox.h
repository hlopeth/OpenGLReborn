#pragma once
#include "Components/DrawComponent.h"
#include "CubeTexture.h"
#include "Shader.h"

class SkyBox : public DrawComponent {
public:
	SkyBox(CubeTexture texture);
	void draw(RenderData& renderData) const override;
private:
	ShaderProgram shader;
	CubeTexture texture;
	GLuint VAO;
    const static GLfloat vertices[];
};