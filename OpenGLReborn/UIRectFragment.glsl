#version 460 core

uniform vec4 u_color;

out vec4 fragmentColor;

void main()
{
	fragmentColor = u_color;
}