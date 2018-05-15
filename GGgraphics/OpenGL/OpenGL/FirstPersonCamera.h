#pragma once
#include "Camera.h"

class FirstPersonCamera : public Camera
{
public:
	~FirstPersonCamera();

	void update(GLFWwindow* window, float deltaTime ) override;

	float getMoveSpeed() const { return m_moveSpeed; };
	void setMoveSpeed(float val) { m_moveSpeed = val; };

private:
	float m_moveSpeed = 10.0f;
	float m_rotationSpeed = glm::pi<float>() * 0.25f;
};

