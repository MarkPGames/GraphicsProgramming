#include "FirstPersonCamera.h"
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>

FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::update(GLFWwindow* window, float deltaTime)
{
	if (window == nullptr) return;

	auto& forward = getTransform()[2];
	auto& right = getTransform()[0];
	auto& up = getTransform()[1];

	auto worldUp = glm::vec4{0, 1, 0, 0};

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		translate(forward * deltaTime * -m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		translate(forward * deltaTime * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		translate(right * deltaTime * -m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		translate(right * deltaTime * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		translate(forward * deltaTime * -m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		translate(forward * deltaTime * m_moveSpeed);
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		translate(up * deltaTime * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		translate(up * deltaTime * -m_moveSpeed);
	}


	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		auto rot = glm::angleAxis(m_rotationSpeed * deltaTime, glm::vec3(up));
		getTransform() *= glm::mat4_cast(rot);

	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		auto rot = glm::angleAxis(-m_rotationSpeed * deltaTime, glm::vec3(up));
		getTransform() *= glm::mat4_cast(rot);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		auto rot = glm::angleAxis(m_rotationSpeed * deltaTime, glm::vec3(right));
		getTransform() *= glm::mat4_cast(rot);

	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		auto rot = glm::angleAxis(-m_rotationSpeed * deltaTime, glm::vec3(right));
		getTransform() *= glm::mat4_cast(rot);
	}
}
