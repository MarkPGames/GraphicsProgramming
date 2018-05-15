#pragma once
#include "Camera.h"

class OrbitCamera : public Camera
{
public:

	virtual void update([[maybe_unused]] GLFWwindow* window, [[maybe_unused]] float deltaTime) override
	{
		m_rotateAngle += m_rotationSpeed;
	}

	void setFocusPoint(glm::vec4 focusPont)
	{
		m_focusPoint = focusPont;
		m_offset = m_focusPoint - getTransform()[3];
		m_rotateAngle = 0.0f;
	}

private:
	glm::vec4 m_focusPoint;
	glm::vec4 m_offset;
	float m_rotateAngle = glm::pi<float>() * 0.25f;
	float m_rotationSpeed = 10.0f;
};

