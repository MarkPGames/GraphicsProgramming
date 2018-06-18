#pragma once
#include "Application.h"
#include <glm/glm.hpp>
#include "FirstPersonCamera.h"
#include <aie/Shader.h>
#include <aie/OBJMesh.h>
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
	void ImGui();
private:
	glm::mat4 view;
	glm::mat4 projection;
	float valueX;
	float valueY;
	FirstPersonCamera m_camera;

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

	struct DirLight
	{
		glm::vec3 direction;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
	DirLight m_dirLight;
	float lightDir;
	glm::vec3 lightDirection;

	struct PointLight 
	{
		glm::vec3 position;

		float constant;	
		float linear;
		float quadratic;
		float intensity;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
	PointLight m_pointLights[4];

	glm::vec3 pointLightPositions[4] = 
	{ 
		glm::vec3(2.5f,  2.0f,  1.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	float gizY ;

};

