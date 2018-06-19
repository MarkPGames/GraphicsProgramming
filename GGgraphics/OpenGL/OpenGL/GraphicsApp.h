#pragma once
#include "Application.h"
#include <glm/glm.hpp>
#include "FirstPersonCamera.h"
#include <aie/Shader.h>
#include <aie/OBJMesh.h>
#include "Mesh.h"
#include "PointLight.h"

class GraphicsApp : public Application
{
public:
	GraphicsApp();
	~GraphicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
	void ImGui();
private:
	glm::mat4 view;
	glm::mat4 projection;
	float valueX;
	float valueY;
	FirstPersonCamera m_camera;

	aie::Input* input;

	aie::ShaderProgram m_shader;
	aie::ShaderProgram m_texturedShader;
	aie::ShaderProgram m_phongShader;

	aie::Texture m_gridTexture;
	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;

	aie::OBJMesh m_dragonMesh;
	glm::mat4 m_dragonTransform;

	aie::Texture m_soulSpearTexture;
	aie::OBJMesh m_soulSpearMesh;
	glm::mat4 m_soulSpearTransform;

	Light m_dirLight;
	float lightDir;

	std::vector<PointLight> m_pointLights;

	float gizY ;

};

