#version 460 core
in vec2 o_texCoord;
in vec3 o_normal;
in vec3 o_fragPos;

out vec4 FragColor;

void main()
{
	FragColor = vec4(0.0, 0.0, 1.0, 1.0);
} 