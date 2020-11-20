#version 460 core
#define max_pointLights 5
out vec4 FragColor;

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPos;
in vec3 vTangent;
in vec3 vBitangent;

struct Material {
	sampler2D texture_diffuse0;
	sampler2D texture_specular0;
	sampler2D texture_normal0;
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
};

uniform vec3 cameraPos;
uniform mat4x4 model;
uniform Material material;
uniform int n_pointLights;
uniform PointLight pointLights[max_pointLights];

float calcDiffusion(vec3 pointLighPos, vec3 normal, vec3 fragPos)
{
	vec3 lightDir = normalize(pointLighPos - fragPos);
	return max(dot(normal,lightDir),0.0f);
}

float getSpecular(vec3 pointLighPos, vec3 normal, vec3 fragPos, vec3 cameraPos)
{
	vec3 lightDir   = normalize(pointLighPos - fragPos);
	vec3 viewDir    = normalize(cameraPos - fragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	return pow(max(dot(normal, halfwayDir), 0.0), 16.0);
}

float getAtenuantion(PointLight pl, float distanceToLight)
{
	return 1.0 / (pl.constant + pl.linear * distanceToLight + pl.quadratic * (distanceToLight * distanceToLight));  
}

mat3 getTBN()
{
    vec3 T = normalize(vec3(model * vec4(vTangent,   0.0)));
    vec3 B = normalize(vec3(model * vec4(vBitangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(vNormal,    0.0)));
	mat3 TBN = transpose(mat3(T, B, N));
	return TBN;
}

vec3 getNormal() 
{
	vec3 normal = texture(material.texture_normal0, vTexCoord).rgb;
    return normalize(normal * 2.0 - 1.0); 
}

vec4 calcLightColor()
{
	mat3 TBN = getTBN();
	vec3 tanNormal = getNormal();
	vec3 tanCameraPos = TBN * cameraPos;
	vec3 tanFragPos = TBN * vFragPos;

	vec4 resultLight = vec4(0.0);
	int n = min(n_pointLights, max_pointLights);
	for(int i = 0; i < n_pointLights; i++)
	{
		float distanceToLight = length(pointLights[i].position - vFragPos);
		float attenuation = getAtenuantion(pointLights[i], distanceToLight);

		vec3 tanLightPos = TBN * pointLights[i].position;

		vec3 materialDiffuse = vec3(1.0);
		vec4 diffuseColor  = vec4(calcDiffusion(tanLightPos, tanNormal, tanFragPos) * (materialDiffuse * pointLights[i].diffuse), 1.0);
		vec3 materialSpec = texture(material.texture_specular0, vTexCoord).xyz;

		vec4 specularColor = vec4(getSpecular(tanLightPos, tanNormal, tanFragPos, tanCameraPos)  * (materialSpec * pointLights[i].specular), 1.0);

		vec3 materialAmbient = vec3(1.0);
		vec4 ambientColor = vec4(materialAmbient * pointLights[i].ambient,1.0);

		resultLight += attenuation * (diffuseColor + specularColor + ambientColor);
	}
	return resultLight;
}

void main()
{
	vec4 diffuseColor = vec4(material.color.r, material.color.g, material.color.b, 1.0);
	vec4 texelColol = texture(material.texture_diffuse0, vTexCoord);

	  

	vec4 lightColor = calcLightColor();
    FragColor = texelColol * lightColor;
	FragColor.a = 1.0;
} 