#include "GraphicsApp.h"
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <aie/Gizmos.h> 
//#include <glm/glm.hpp>
#include <glm/ext.hpp> 
#include <iostream>
#include <imgui.h>
#include <aie/Input.h>
#include "imgui_glfw3.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using namespace aie;

GraphicsApp::GraphicsApp()
{

}


GraphicsApp::~GraphicsApp()
{
}

bool GraphicsApp::startup()
{
	setBackgroundColour(0.25f, 0.25f, 0.25f, 1.0f);

	Gizmos::create(10000, 10000, 10000, 10000);

	//light
	PointLight* newPLight = new PointLight();
	m_pointLights.push_back(*newPLight);
	lightDir = 1.5f;

	projection = glm::perspective(glm::pi<float>() * 0.25f, (float)getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f);
	m_camera.setProjectionMatrix(projection);

	//load vertex shader from file
	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	//load fragment shader from file
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");

	if (m_phongShader.link() == false)
	{
		printf("Phong Shader Error: %s\n", m_phongShader.getLastError());
		system("pause");
		return false;
	}
	if (m_gridTexture.load("./textures/numbered_grid.tga") == false)
	{
		printf("Failed to load texture!\n");
		system("pause");
		return false;
	}

	m_quadMesh.initialiseQuad();

	//make the quad 10 units wide
	m_quadTransform = 
	{
	10, 0, 0, 0,
	0,10,0,0,
	0,0,10,0,
	0,0,0,1
	};

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	valueY = 10;
	valueX = 10;


	if (m_dragonMesh.load("./models/palmtrees/palm_tree.obj", true, true) == false)
	{
		printf("Dragon Mesh Error!\n");
		system("pause");
		return false;
	}

	m_dragonTransform = 
	{
	0.02f, 0, 0, 0,
	0, 0.02f, 0, 0,
	0, 0, 0.02f, 0,
	-2.5, 0, 0, 1
	};

	if (m_soulSpearMesh.load("./models/soulspear/soulspear.obj", true, true) == false)
	{
	printf("Soulspear Mesh Error!\n");
	system("pause");
	return false;
	}

	m_soulSpearTransform =
	{
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	2.5,0,0,1
	};

	ImGui_Init(m_window, true);

	return true;
}

void GraphicsApp::shutdown()
{
	aie::Gizmos::destroy();
	ImGui_Shutdown();
	destroyWindow();
}

void GraphicsApp::update(float deltaTime)
{
	ImGui_NewFrame();
	input = Input::getInstance();
	// query time since application started
	float time = getTime();

	//m_dirLight.setDirection(dLightPos);
	// rotate light
	m_dirLight.setDirection(lightDir);

	m_camera.update(getWindow(), input, deltaTime);
	
	if (glfwGetKey(getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		PointLight* newPointLight = new PointLight();
		m_pointLights.push_back(*newPointLight);
	}

	if (glfwGetKey(getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		quit();
	}

}

void GraphicsApp::draw()
{
	clearScreen();

	auto pvm = m_camera.getProjectionMatrix() * m_camera.getViewMatrix() *  m_soulSpearTransform;

	m_phongShader.bind();

	// bind directional light
	m_phongShader.bindUniform("cameraPosition", m_camera.getPosition());
	m_phongShader.bindUniform("dirLight.ambient", *m_dirLight.getAmbient());
	m_phongShader.bindUniform("dirLight.diffuse", *m_dirLight.getDiffuse());
	m_phongShader.bindUniform("dirLight.specular", *m_dirLight.getSpecular());
	m_phongShader.bindUniform("dirLight.direction", *m_dirLight.getDirection());

	//bind point lights
	for (int i = 0; i < m_pointLights.size(); i++)
	{
		m_phongShader.bindUniform("pointLights[0].constant", 1.0f);
		m_phongShader.bindUniform("pointLights[0].linear", 1.0f);
		m_phongShader.bindUniform("pointLights[0].quadratic", 1.0f);
		m_phongShader.bindUniform("pointLights[0].intensity", *m_pointLights[i].getIntensity());
		m_phongShader.bindUniform("pointLights[0].position", *m_pointLights[i].getPosition());
		m_phongShader.bindUniform("pointLights[0].diffuse", *m_pointLights[i].getDiffuse());
		m_phongShader.bindUniform("pointLights[0].specular", *m_pointLights[i].getSpecular());
		m_phongShader.bindUniform("pointLights[0].ambient", *m_pointLights[i].getAmbient());
	}

	pvm = m_camera.getProjectionMatrix() * m_camera.getViewMatrix() * m_soulSpearTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	// bind transforms for lighting
	m_phongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_soulSpearTransform)));
	m_phongShader.bindUniform("ModelMatrix", m_soulSpearTransform);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	m_soulSpearMesh.draw();

	pvm = m_camera.getProjectionMatrix() * m_camera.getViewMatrix() * m_dragonTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	// bind transforms for lighting
	m_phongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_dragonTransform)));
	m_phongShader.bindUniform("ModelMatrix", m_dragonTransform);


	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	m_dragonMesh.draw();

	Gizmos::clear();

	Gizmos::addTransform(glm::mat4(1), 10.0f);

	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	vec4 yellow(1, 1, 0, 1);
	for (int i = 0; i < 21; i++)
	{
		Gizmos::addLine(vec3(-10 + i, gizY, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);

		Gizmos::addLine(vec3(10, gizY, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}

	Gizmos::addSphere(*m_pointLights[0].getPosition(), 0.1, 8, 8, black);
	Gizmos::addAABBFilled(*m_dirLight.getDirection(), glm::vec3(0.1, 0.1, 0.1), black);

	glEnable(GL_DEPTH_TEST);
	Gizmos::draw(m_camera.getProjectionMatrix() * m_camera.getViewMatrix());

	ImGui();
}

void GraphicsApp::ImGui()
{
	ImGui::Begin("Editor");

	//Direction Light
	ImGui::Text("Toggle Camera:");
	ImGui::SameLine();
	ImGui::Checkbox("(Left Ctrl)", &m_camera.mouseToggle);

	ImGui::Text("Direction:");
	ImGui::SameLine();
	ImGui::SliderFloat("", &lightDir, 0.0f, glm::pi<float>() * 2);
	//Point Light
	if (ImGui::CollapsingHeader("Point Light"))
	{
		ImGui::InputFloat("x: ", m_pointLights[0].getPositionX(), 0.5);
		ImGui::InputFloat("y: ", m_pointLights[0].getPositionY(), 0.5);
		ImGui::InputFloat("z: ", m_pointLights[0].getPositionZ(), 0.5);
		ImGui::SliderFloat("intensity", m_pointLights[0].getIntensity(), 0, 100);
	}

	ImGui::End();
	ImGui::Render();
}
