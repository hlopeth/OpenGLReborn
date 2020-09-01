#version 460 core
in vec2 o_texCoord;
in vec3 o_normal;
in vec3 o_fragPos;

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	vec3 color;
};
uniform Material material;

out vec4 FragColor;

void main()
{
	FragColor = vec4(material.color.r, material.color.g, material.color.b, 1.0);
} 