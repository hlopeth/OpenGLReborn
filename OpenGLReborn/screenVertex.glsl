#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
    TexCoords = aTexCoords;
    TexCoords.y = 1 - TexCoords.y;
    gl_Position = vec4(aPos.x, aPos.z, 0.0, 1.0); 
}  