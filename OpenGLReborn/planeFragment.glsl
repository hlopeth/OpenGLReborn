#version 330 core
#define max_pointLights 5
out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;
in vec4 fragPosInLightSpace;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct PointLight {
	vec3 position;
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform sampler2D texture1;
uniform sampler2D depthMap;
uniform vec3 cameraPos;
uniform Material material;
uniform int n_pointLights;
uniform PointLight pointLights[max_pointLights];

float calcDiffusion(PointLight pointLight)
{
	vec3 lightDir = normalize(pointLight.position-fragPos);
	return max(dot(normal,lightDir),0.0f);
}

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
	float near_plane = 0.1;
	float far_plane = 100.0;
    return (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));
}

float calcSpecular(PointLight pointLight)
{
	vec3 lightDir = normalize(pointLight.position-fragPos);
	vec3 view = normalize(cameraPos-fragPos);
	lightDir = reflect(-lightDir, normal);
	return pow(max(dot(view,lightDir),0.0f),material.shininess);
}

float shadowCalic()
{
	vec3 projCoords = fragPosInLightSpace.xyz / fragPosInLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = LinearizeDepth(texture(depthMap, projCoords.xy).r);
	float currentDepth = projCoords.z;  
	float bias =0.002;// max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
	//float shadow = currentDepth-bias > closestDepth ? 0.0 : 1.0;  
	//shadow = currentDepth > 1.0 ? 1.0 : shadow;

	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(depthMap, 0);
	for(int x = -1; x <= 1; ++x)
	{
	    for(int y = -1; y <= 1; ++y)
	    {
	        float pcfDepth = texture(depthMap, projCoords.xy + vec2(x, y) * texelSize).r; 
	        shadow += currentDepth - bias > pcfDepth ? 0.0 : 1.0;        
	    }    
	}
	shadow /= 9.0;

	return shadow;
}

vec4 calcLightColor()
{
	vec4 resultLight = vec4(0.0);
	int n = min(n_pointLights, max_pointLights);

	float shadow = shadowCalic();

	for(int i=0;i<n_pointLights;i++)
	{
		float distanceToLight = length(pointLights[i].position - fragPos);
		float attenuation = 1.0 / (pointLights[i].constant + pointLights[i].linear * distanceToLight + pointLights[i].quadratic * (distanceToLight * distanceToLight));    
		vec4 diffuseColor  = vec4(calcDiffusion(pointLights[i]) * (material.diffuse * pointLights[i].diffuse)  ,1.0);
		vec4 specularColor = vec4(calcSpecular(pointLights[i])  * (material.specular * pointLights[i].specular) ,1.0);
		vec4 ambientColor = vec4(material.ambient * pointLights[i].ambient,1.0);
		resultLight += attenuation*(shadow*(diffuseColor + specularColor) + ambientColor);
	}
	return resultLight;
}

void main()
{
	vec4 texelColol = texture(texture1, texCoord);
	vec4 lightColor = calcLightColor();
    FragColor = texelColol*lightColor;
} 