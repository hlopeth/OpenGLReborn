#version 460 core
in vec2 o_texCoord;
in vec3 o_normal;
in vec3 o_fragPos;

struct DirectionalLight {
	vec3 direction;
	vec3 color;
};

struct Material {
	sampler2D texture_diffuse;
	vec3 color;
};

uniform Material material;
uniform DirectionalLight directionalLight;

out vec4 FragColor;

vec4 calcDirLightColor() {
	vec3 diffuse = vec3(max(dot(o_normal, directionalLight.direction), 0.2f));
	return vec4(diffuse * directionalLight.color, 1.0);
}

void main()
{
	vec4 texel = texture(material.texture_diffuse, o_texCoord);
	FragColor = texel * calcDirLightColor();
} 