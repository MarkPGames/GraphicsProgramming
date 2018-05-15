#pragma once
#include "Application.h"
#include <glm/glm.hpp>
#include "FirstPersonCamera.h"
#include <aie/Shader.h>
#include "Mesh.h"

class GraphicsApp : public Application
{
public:
	GraphicsApp();
	~GraphicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
private:
	glm::mat4 view;
	glm::mat4 projection;
	float valueX;
	float valueY;
	FirstPersonCamera m_camera;
	aie::ShaderProgram m_shader;
	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;

};

