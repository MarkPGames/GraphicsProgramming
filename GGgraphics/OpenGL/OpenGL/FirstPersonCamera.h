#pragma once
#include "Camera.h"

class FirstPersonCamera : public Camera
{
public:
	FirstPersonCamera();
	~FirstPersonCamera();

	void update(GLFWwindow* window, aie::Input* input, float deltaTime ) override;

	float getMoveSpeed() const { return m_moveSpeed; };
	void setMoveSpeed(float val) { m_moveSpeed = val; };

	double mouseX;
	double mouseY;
	double deltaMouseX;
	double deltaMouseY;
	glm::vec3 up;

	bool mouseToggle = false;
	bool wasPressed = false;

private:
	float m_moveSpeed = 10.0f;
	float m_rotationSpeed = glm::pi<float>() * 0.25f;
	int windowWidth;
	int windowHeight;
};

