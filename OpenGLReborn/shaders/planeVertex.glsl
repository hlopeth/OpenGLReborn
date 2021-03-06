#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;
out vec4 fragPosInLightSpace;

uniform mat4x4 mvp;
uniform mat4x4 model;
uniform mat4x4 lightSpaceMat;



void main()
{
	texCoord = aTexCoord;
	normal = normalize(transpose(inverse(mat3(model)))*aNormal);
	fragPos = vec3(model*vec4(aPos,1.0));
	fragPosInLightSpace = lightSpaceMat * vec4(fragPos,1.0);
    gl_Position = mvp*vec4(aPos.x, aPos.y, aPos.z, 1.0);
}