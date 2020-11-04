#version 460 core
in vec2 o_texCoord;
in vec3 o_normal;
in vec3 o_fragPos;

struct Material {
	sampler2D texture_diffuse;
	vec3 color;
};
uniform Material material;

out vec4 FragColor;

void main()
{
	FragColor = texture(material.texture_diffuse, o_texCoord);
} 