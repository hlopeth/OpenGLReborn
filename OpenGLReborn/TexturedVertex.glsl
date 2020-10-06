#version 460 core
layout (location = 0) in vec3 i_position;
layout (location = 1) in vec3 i_normal;
layout (location = 2) in vec2 i_texCoord;

uniform mat4x4 mvp;
uniform mat4x4 model;

out vec2 o_texCoord;
out vec3 o_normal;
out vec3 o_fragPos;

void main() 
{
	o_texCoord = i_texCoord;
	o_normal = normalize(transpose(inverse(mat3(model))) * i_normal);
//	o_normal = i_normal;
	o_fragPos = vec3(model * vec4(i_position,1.0));
    gl_Position = mvp * vec4(i_position, 1.0);
}
