#include "FirstPersonCamera.h"
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <aie/Input.h>

FirstPersonCamera::FirstPersonCamera()
{
	resetPosition();
}

FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::update(GLFWwindow* window, aie::Input* input, float deltaTime)
{
	if (window == nullptr) return;
	wasPressed = false;

	if (input->wasKeyPressed(aie::INPUT_KEY_LEFT_CONTROL))
	{
		if (mouseToggle == true)
		{
			mouseToggle = false;
		}
		else
		{
			mouseToggle = true;
			glfwSetCursorPos(window, windowWidth, windowHeight);
		}
		
	}

	if (mouseToggle == true)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);


		//int windowWidth, windowHeight; // Get the width and height from the window
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		windowWidth = windowWidth >> 1; // Half them
		windowHeight = windowHeight >> 1;

		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Get mouse pos relative to the centre of the screen
		deltaMouseX = (windowWidth - mouseX);
		deltaMouseY = (windowHeight - mouseY);

		glfwSetCursorPos(window, windowWidth, windowHeight);

		glm::vec4 up = getViewMatrix() * glm::vec4(0, 1, 0, 0);
		glm::mat4 rotMatrix(1.0f);

		rotMatrix = glm::rotate(rotMatrix, (float)deltaMouseX * 0.04f * deltaTime, glm::vec3(up[0], up[1], up[2]));
		getTransform() *= rotMatrix;

		rotMatrix = glm::rotate(rotMatrix, (float)deltaMouseY * 0.04f * deltaTime, glm::vec3(1, 0, 0));
		getTransform() *= rotMatrix;


		if (glfwGetKey(window, GLFW_KEY_W))
		{
			translate(-(getTransform()[2] * deltaTime * getMoveSpeed()));
		}
		if (glfwGetKey(window, GLFW_KEY_S))
		{
			translate(getTransform()[2] * deltaTime * getMoveSpeed());
		}
		if (glfwGetKey(window, GLFW_KEY_A))
		{
			translate(-(getTransform()[0] * deltaTime * getMoveSpeed()));
		}
		if (glfwGetKey(window, GLFW_KEY_D))
		{
			translate(getTransform()[0] * deltaTime * getMoveSpeed());
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			translate(up * deltaTime * m_moveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			translate(up * deltaTime * -m_moveSpeed);
		}

		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		{
			resetPosition();
		}
	}
	else
	{

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}



}
