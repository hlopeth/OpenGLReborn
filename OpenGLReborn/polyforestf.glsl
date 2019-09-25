#version 460 core
#define max_pointLights 5
out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	vec3 color;
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

uniform vec3 cameraPos;
uniform Material material;
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

	float offset  = 0.1;
	float samples = 4.0;
	for(float x = -offset; x < offset; x += offset / (samples * 0.5))
	{
	    for(float y = -offset; y < offset; y += offset / (samples * 0.5))
	    {
	        for(float z = -offset; z < offset; z += offset / (samples * 0.5))
	        {
	            float closestDepth = texture(shadowCubeMap, vec4(fragToLight + vec3(x, y, z), level)).r; 
	            closestDepth *= pointLight.farPlane;   // Undo mapping [0;1]
	            if(currentDepth - bias < closestDepth)
	                shadow += 1.0;
	        }
	    }
	}
	shadow /= (samples * samples * samples);
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

vec4 calcLightColor()
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
		float shadow = calcShadow(pointLights[i], shadowCubeMaps, i);
		resultLight += shadow*attenuation*(diffuseColor + specularColor + ambientColor)/n_pointLights;
	}
//	vec3 fragToLight = fragPos - pointLights[0].position; 
//    resultLight = vec4(vec3(texture(shadowCubeMaps, vec4(fragToLight, 0)).r),0.0);
//	vec3 fragToLight = fragPos - pointLights[1].position; 
//    resultLight = vec4(vec3(texture(shadowCubeMaps, vec4(fragToLight, 1)).r),0.0);
	return resultLight;
}

void main()
{
	vec4 diffuseColor = vec4(material.color.r,material.color.g,material.color.b,1.0);
	vec4 texelColol = texture(material.texture_diffuse1, texCoord);
	vec4 lightColor = calcLightColor();
    FragColor = diffuseColor*lightColor;
//	FragColor = lightColor;
} 