// classic Phong fragment shader
#version 410

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vTangent;
in vec3 vBiTangent;

//uniform sampler2D ambientTexture;
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

uniform vec3 cameraPosition;

uniform vec3 Ka; //ambient material colour
uniform vec3 Kd; //diffuse material colour
uniform vec3 Ks; //specular material colour 
uniform float specularPower; //material specular power

struct DirLight 
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NR_POINT_LIGHTS 1
uniform PointLight pointLights[NR_POINT_LIGHTS];

out vec4 FragColour;


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(light.direction);
	
	// calculate lambert term (negate light direction)
	float lambertTerm = max( 0, min( 1, dot( normal, -lightDir ) ));
	
	vec3 texDiffuse = texture(diffuseTexture, vTexCoord).rgb;
	vec3 texSpecular = texture(specularTexture, vTexCoord).rgb;
	
	//specular shading
	vec3 R = reflect(lightDir, normal);
	//calculate specular term
	float specularTerm = pow(max(0, dot(R, viewDir) ), specularPower);
	
	//combine results
	vec3 ambient = light.ambient * Ka;
	vec3 diffuse = light.diffuse * Kd * texDiffuse * lambertTerm;
	vec3 specular = light.specular * Ks * texSpecular * specularTerm;
	return(ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
vec3 lightDir = normalize(fragPos - light.position);
	
	// calculate lambert term (negate light direction)
	float lambertTerm = max( 0, min( 1, dot( normal, -lightDir ) ));
	
	vec3 texDiffuse = texture(diffuseTexture, vTexCoord).rgb;
	vec3 texSpecular = texture(specularTexture, vTexCoord).rgb;
	
	//specular shading
	vec3 R = reflect(lightDir, normal);
	//calculate specular term
	float specularTerm = pow(max(0, dot(R, viewDir) ), specularPower);
	//attenuation
	float dist = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
	
	//combine results
	vec3 ambient = light.ambient * Ka;
	vec3 diffuse = light.diffuse * Kd * texDiffuse * lambertTerm;
	vec3 specular = light.specular * Ks * texSpecular * specularTerm;
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return(ambient + diffuse + specular);
}

void main()
{
	// ensure normal and light direction are normalised
	vec3 N = normalize(vNormal);
	//vec3 L = normalize(LightDirection);
	vec3 T = normalize(vTangent);
	vec3 B = normalize(vBiTangent);
	
	vec3 texNormal = texture(normalTexture, vTexCoord ).rgb;
		
	mat3 TBN = mat3(T, B, N);
	N = TBN * (texNormal * 2 - 1);
	
	//calculate view vector and reflection vector
	vec3 V = normalize(cameraPosition - vPosition.xyz);

	//Directional lighting
	vec3 result = CalcDirLight(dirLight, N, V);
	//Point lights
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		result += CalcPointLight(pointLights[i], N, vPosition.xyz, V);
	}
	
	//output final colour
	FragColour = vec4(result, texture(diffuseTexture, vTexCoord).a);
}

