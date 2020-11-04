#version 460 core
in vec2 o_texCoord;
in vec3 o_normal;
in vec3 o_fragPos;

uniform vec3 color;

out vec4 FragColor;

void main()
{
	FragColor = vec4(color.r, color.g, color.b, 1.0);
} 