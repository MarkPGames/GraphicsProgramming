#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using namespace glm;
class Light
{
	//Only for directional light
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

public:
	Light() 
	{ 
		direction = { 1.0f, 1.0f, 1.0f };
		ambient = {0.25f, 0.25f, 0.25f};
		diffuse = { 1.0f, 1.0f, 0.8f };
		specular = { 1.0f, 1.0f, 0.8f };
	};
	virtual ~Light() { ; };

	const vec3* getDirection() { return &direction; };
	//Takes in an angle in radians
	void setDirection(float a_angle) 
	{ 
		direction = glm::normalize(vec3(glm::cos(a_angle), glm::sin(a_angle), 1.0f)); 
	};

	vec3* getAmbient() { return &ambient; };
	void setAmbient(vec3 a_ambient) { ambient = a_ambient; };

	vec3* getDiffuse() { return &diffuse; };
	void setDiffuse(vec3 a_diffuse) { diffuse = a_diffuse; }; 

	vec3* getSpecular() { return &specular; };
	void setSpecular(vec3 a_specular) { specular = a_specular; };
};

