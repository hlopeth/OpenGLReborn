#version 460 core
layout (location = 0) in vec3 i_position;
layout (location = 1) in vec2 i_texCoord;
layout (location = 2) in vec3 i_normal;

uniform mat4x4 mvp;
uniform mat4x4 model;

void main() 
{
    gl_Position = mvp * vec4(i_position, 1.0);
}

