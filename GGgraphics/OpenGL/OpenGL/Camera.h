#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

struct GLFWwindow;

class Camera
{
public:
	virtual ~Camera();

	void setPosition(glm::vec4 position);
	glm::vec4 getPosition() const;
	void translate(glm::vec4 positionModifier);

	const glm::mat4& getTransform() const { return m_worldTransform; };
	glm::mat4& getTransform() { return m_worldTransform; };

	glm::mat4 getViewMatrix() const { return glm::inverse(m_worldTransform); };
	const glm::mat4& getProjectionMatrix() const;
	void setProjectionMatrix(glm::mat4 projectionMatrix);

	void lookAt(glm::vec4 focusPoint, glm::vec3 up = { 0,1,0 });

	virtual void update(GLFWwindow* window, float deltaTime) {};

private:
	glm::mat4 m_worldTransform = glm::mat4(1);
	glm::mat4 m_projectionMatrix = glm::mat4(1);
	bool m_hasSetProjectMatrix = false;
};