#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

uniform mat4x4 mvp;
uniform mat4x4 model;

void main()
{
	texCoord = aTexCoord;
	normal = normalize(transpose(inverse(mat3(model)))*aNormal);
	fragPos = vec3(model*vec4(aPos,1.0));
    gl_Position = mvp*vec4(aPos.x, aPos.y, aPos.z, 1.0);
}