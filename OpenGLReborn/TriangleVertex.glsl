#version 460 core

layout (location = 0) in vec2 position;

out vec2 color;

void main() 
{
	color = position;
	gl_Position = vec4(position.x, position.y, 0, 1.0);
}