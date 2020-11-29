#version 460 core
in vec3 o_texCoord;

out vec4 FragColor;

uniform samplerCube skybox;

void main()
{
	FragColor = texture(skybox, o_texCoord);
}