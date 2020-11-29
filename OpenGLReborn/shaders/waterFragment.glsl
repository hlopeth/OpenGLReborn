#version 460 core
in vec2 o_texCoord;
in vec3 o_normal;
in vec3 o_fragPos;
in float o_noise;

struct DirectionalLight {
	vec3 direction;
	vec3 color;
};

uniform DirectionalLight directionalLight;
uniform vec3 cameraPos;
uniform vec4 color;

out vec4 FragColor;

float getSpecular(vec3 lightDir, vec3 normal, vec3 fragPos, vec3 cameraPos)
{
	vec3 viewDir    = normalize(cameraPos - fragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	return pow(max(dot(normal, halfwayDir), 0.0), 16.0);
}

vec4 calcDirLightColor() {
	vec3 diffuse = vec3(max(dot(o_normal, directionalLight.direction), 0.2f));
	float specular = getSpecular(directionalLight.direction, o_normal, o_fragPos, cameraPos);
	return vec4(diffuse * directionalLight.color + specular, 1.0);
}

void main()
{
	vec4 diffuseColor = vec4(color.rgb + clamp(o_noise, 0.0, 1.0), color.a);
	vec4 lightColor = calcDirLightColor();
	FragColor = diffuseColor;
} 