#version 460 core
in vec2 o_texCoord;
in vec3 o_normal;
in vec3 o_fragPos;

uniform vec4 color;

out vec4 FragColor;

void main()
{
	FragColor = vec4(color);
} 