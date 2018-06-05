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

uniform vec3 AmbientColour; //ambient light colour
uniform vec3 DiffuseColour; //diffuse light colour
uniform vec3 SpecularColour; //specular light colour
uniform vec3 LightDirection;

out vec4 FragColour;

void main()
{
	// ensure normal and light direction are normalised
	vec3 N = normalize(vNormal);
	vec3 L = normalize(LightDirection);
	vec3 T = normalize(vTangent);
	vec3 B = normalize(vBiTangent);
	
	mat3 TBN = mat3(T, B, N);
	
	vec3 texDiffuse = texture(diffuseTexture, vTexCoord).rgb;
	vec3 texSpecular = texture(specularTexture, vTexCoord).rgb;
	vec3 texNormal = texture(normalTexture, vTexCoord ).rgb;
	
	N = TBN * (texNormal * 2 - 1);
	
	// calculate lambert term (negate light direction)
	float lambertTerm = max( 0, min( 1, dot( N, -L ) ));
	
	//calculate view vector and reflection vector
	vec3 V = normalize(cameraPosition - vPosition.xyz);
	vec3 R = reflect(L, N);
	
	//calculate specular term
	float specularTerm = pow(max(0, dot(R, V) ), specularPower);
	
	//calculate each colour property
	vec3 ambient = AmbientColour * Ka;
	vec3 diffuse = DiffuseColour * Kd  * texDiffuse * lambertTerm;
	vec3 specular = SpecularColour * Ks * texSpecular * specularTerm;
	
	//output final colour
	FragColour = vec4(ambient + diffuse + specular, texture(diffuseTexture, vTexCoord).a);
}

