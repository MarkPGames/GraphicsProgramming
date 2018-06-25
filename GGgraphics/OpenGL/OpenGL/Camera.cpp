#include "Camera.h"

Camera::~Camera()
{
}

void Camera::setPosition(glm::vec4 position)
{
	m_worldTransform[3] = position;
}

glm::vec4 Camera::getPosition() const
{
	return m_worldTransform[3];
}

void Camera::resetPosition()
{
	m_worldTransform[3] = {0, 2, 10, 1};
}

void Camera::translate(glm::vec4 positionModifier)
{
	m_worldTransform[3] += positionModifier;
}

const glm::mat4 & Camera::getProjectionMatrix() const
{
	assert(m_hasSetProjectMatrix == true);
	{
		return m_projectionMatrix;
	}
}

void Camera::setProjectionMatrix(glm::mat4 projectionMatrix)
{
	m_hasSetProjectMatrix = true;
	m_projectionMatrix = projectionMatrix;
}

void Camera::lookAt(glm::vec4 focusPoint, glm::vec3 up)
{
	auto view = glm::lookAt(glm::vec3(m_worldTransform[3]), glm::vec3(focusPoint), up);
	m_worldTransform = glm::inverse(view);
}
