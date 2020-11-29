#version 460 core
layout (location = 0) in vec3 i_position;

uniform mat4x4 mvp;

out vec3 o_texCoord;

void main() 
{
	o_texCoord = i_position;
    vec4 pos = mvp * vec4(i_position, 1.0);
	gl_Position = pos.xyww;
}
