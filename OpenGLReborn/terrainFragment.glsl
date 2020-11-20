#version 460 core
#define max_pointLights 5
out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;
in vec3 alphas;

struct DirectinalLight {
	vec3 direction;
	vec3 color;
	vec3 ambient;
};

struct PointLight {
	vec3 position;
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
    float farPlane;
};

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	vec3 color;
};
uniform Material sandMaterial;
uniform Material grassMaterial;
uniform Material rockMaterial;

uniform DirectinalLight directinalLight;
uniform vec3 cameraPos;
uniform int n_pointLights;
uniform PointLight pointLights[max_pointLights];
uniform samplerCubeArray shadowCubeMaps;

float calcShadow(PointLight pointLight, samplerCubeArray shadowCubeMap, int level)
{
	vec3 fragToLight = fragPos - pointLight.position; 
    float closestDepth = texture(shadowCubeMap, vec4(fragToLight, level)).r;
	closestDepth *= pointLight.farPlane;
	float currentDepth = length(fragToLight);
    float bias = 0.1; 
    float shadow = currentDepth -  bias > closestDepth ? 0.0 : 1.0;
    return shadow;
}

float calcDiffusion(PointLight pointLight)
{
	vec3 lightDir = normalize(pointLight.position-fragPos);
	return max(dot(normal,lightDir),0.0f);
}

float calcSpecular(PointLight pointLight)
{
	vec3 lightDir   = normalize(pointLight.position - fragPos);
	vec3 viewDir    = normalize(cameraPos - fragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	return pow(max(dot(normal, halfwayDir), 0.0), 16.0);
}

vec4 calcPointLightsColor()
{
	vec4 resultLight = vec4(0.0);
	int n = min(n_pointLights, max_pointLights);
	for(int i = 0; i < n_pointLights; i++)
	{
		float distanceToLight = length(pointLights[i].position - fragPos);
		float attenuation = 1.0 / (pointLights[i].constant + pointLights[i].linear * distanceToLight + pointLights[i].quadratic * (distanceToLight * distanceToLight));  
		vec3 materialDiffuse = vec3(1.0);
		vec4 diffuseColor  = vec4(calcDiffusion(pointLights[i]) * (materialDiffuse * pointLights[i].diffuse)  ,1.0);
		vec4 specularColor = vec4(calcSpecular(pointLights[i])  * pointLights[i].specular ,1.0);
		vec3 materialAmbient = vec3(1.0);
		vec4 ambientColor = vec4(materialAmbient * pointLights[i].ambient,1.0);
		//float shadow = calcShadow(pointLights[i], shadowCubeMaps, i);
		resultLight += /*shadow**/attenuation*(diffuseColor + specularColor + ambientColor)/n_pointLights;
	}
	return resultLight;
}

vec4 calcDirLightColor() {
	vec3 diffuse = vec3(max(dot(normal, directinalLight.direction), 0.0f));
	return vec4(diffuse * directinalLight.color + directinalLight.ambient, 1.0);
}

void main()
{
	vec4 sandColor = texture(sandMaterial.texture_diffuse1, texCoord);
	vec4 grassColor = texture(grassMaterial.texture_diffuse1, texCoord);
	vec4 rockColor = texture(rockMaterial.texture_diffuse1, texCoord);

	vec4 diffuseColor = sandColor * alphas.x + grassColor * alphas.y + rockColor * alphas.z;

	vec4 lightColor = calcPointLightsColor() + calcDirLightColor();
    FragColor = diffuseColor * lightColor;
} 