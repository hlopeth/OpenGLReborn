#version 330 core
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
uniform samplerCube shadowCubeMaps[max_pointLights];
//uniform samplerCube shadowCubeMap0;
//uniform samplerCube shadowCubeMap1;
//uniform samplerCube shadowCubeMap2;


float calcShadow(PointLight pointLight, samplerCube shadowCubeMap)
{
	vec3 fragToLight = fragPos - vec3(  -8.0f, 8.0f, -5.0f);//pointLight.position; 
    float closestDepth = texture(shadowCubeMap, fragToLight).r;
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
	            float closestDepth = texture(shadowCubeMap, fragToLight + vec3(x, y, z)).r; 
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
		float shadow = calcShadow(pointLights[i], shadowCubeMaps[i]);
		//resultLight += shadow*attenuation*(diffuseColor + specularColor + ambientColor);
		resultLight += vec4(vec3(shadow),0.0);
	}
	//resultLight += vec4(vec3(calcShadow(pointLights[1], shadowCubeMaps[0])),0.0);
	//resultLight += vec4(vec3(calcShadow(pointLights[1], shadowCubeMap1)),0.0);
	//vec3 fragToLight = fragPos - pointLights[1].position; 
    //resultLight = vec4(vec3(texture(shadowCubeMap0, fragToLight).r),0.0);
	//resultLight = vec4(vec3(pointLights[0].farPlane),0.0);
	return resultLight;
}

void main()
{
	vec4 diffuseColor = vec4(material.color.r,material.color.g,material.color.b,1.0);
	vec4 texelColol = texture(material.texture_diffuse1, texCoord);
	vec4 lightColor = calcLightColor();
    FragColor = diffuseColor*lightColor;
	FragColor = lightColor;
} 