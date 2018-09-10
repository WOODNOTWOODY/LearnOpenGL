#version 330 core
out vec4 fragColor;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	float constant;
	float linear;
	float quadratic;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	float outerSpot;
	float innerSpot;
	float constant;
	float linear;
	float quadratic;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define MAX_POINT_LIGHTS 4
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoord;

uniform vec3 cameraPos;
uniform DirLight dirLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform Material material;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 norm = normalize(fragNormal);
	vec3 viewDir = normalize(cameraPos - fragPos);
	vec3 result = CalcDirLight(dirLight, norm, viewDir);
	for(int i = 0; i < MAX_POINT_LIGHTS; ++i)
	{
		result += CalcPointLight(pointLights[i], norm, fragPos, viewDir);
	}
	result += CalcSpotLight(spotLight, norm, fragPos, viewDir);
	fragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, fragTexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, fragTexCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, fragTexCoord));
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	vec3 ambient = attenuation * light.ambient * vec3(texture(material.diffuse, fragTexCoord));
	vec3 diffuse = attenuation * light.diffuse * diff * vec3(texture(material.diffuse, fragTexCoord));
	vec3 specular = attenuation * light.specular * spec * vec3(texture(material.specular, fragTexCoord));
	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.innerSpot - light.outerSpot;
	float intensity = clamp((theta - light.outerSpot) / epsilon, 0.0, 1.0);
	vec3 ambient = attenuation * intensity * light.ambient * vec3(texture(material.diffuse, fragTexCoord));
	vec3 diffuse = attenuation * intensity * light.diffuse * diff * vec3(texture(material.diffuse, fragTexCoord));
	vec3 specular = attenuation * intensity * light.specular * spec * vec3(texture(material.specular, fragTexCoord));
	return (ambient + diffuse + specular);
}
