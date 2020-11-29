#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vFragPos;
out vec3 vTangent;
out vec3 vBitangent;

uniform mat4x4 mvp;
uniform mat4x4 model;

void main()
{
	vTangent = aTangent;
	vBitangent = aBitangent;
	vTexCoord = aTexCoord;
	vNormal = normalize(transpose(inverse(mat3(model))) * aNormal);
	vFragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = mvp*vec4(aPos, 1.0);
}