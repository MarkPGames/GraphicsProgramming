#pragma once
#include "Light.h"

class PointLight : public Light
{
	vec3 position;
	float constant;
	float linear;
	float quadratic;
	float intensity;

public:
	PointLight() : Light()
	{ 
		position = { 1.0f, 1.0f, 1.0f };
		constant = 1.0f;
		linear = 1.0f;
		quadratic = 1.0f;
		intensity = 1.0f;
	};
	~PointLight() { };

	vec3* getPosition() { return &position; };
	float* getPositionX() { return &position.x; };
	float* getPositionY() { return &position.y; };
	float* getPositionZ() { return &position.z; };
	void setPosition(vec3 a_position) { position = a_position; };

	float getConstant() { return constant; };
	void setConstant(float a_constant) { constant = a_constant; };

	float getLinear() { return linear; };
	void setLinear(float a_linear) { linear = a_linear;  };

	float getQuadratic() { return quadratic; };
	void setQuadratic(float a_quadratic) { quadratic = a_quadratic; };

	float* getIntensity() { return &intensity; };
	void setIntensity(float a_intensity) { intensity = a_intensity; };
};

