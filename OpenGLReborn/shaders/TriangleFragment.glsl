#version 460 core

in vec2 color;

out vec4 fragmentColor;

void main()
{
	fragmentColor = vec4(color, 0.0f, 1.0f);
}