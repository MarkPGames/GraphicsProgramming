#include "GraphicsApp.h"
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <aie/Gizmos.h> 
//#include <glm/glm.hpp>
#include <glm/ext.hpp> 
#include <iostream>


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

	m_light.diffuse = {1, 1, 0};
	m_light.specular = {1, 1, 0};
	m_ambientLightColour = {0.25f, 0.25f, 0.25f};

	projection = glm::perspective(glm::pi<float>() * 0.25f, (float)getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f);
	m_camera.setProjectionMatrix(projection);

	//load vertex shader from file
	m_shader.loadShader(aie::eShaderStage::VERTEX,  "./shaders/simple.vert");
	m_texturedShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/textured.vert");
	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	//load fragment shader from file
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");
	m_texturedShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/textured.frag");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");

	if (m_shader.link() == false)
	{
		printf("Shader Error: %s\n", m_shader.getLastError());
		system("pause");
		return false;
	}
	if (m_texturedShader.link() == false)
	{
		printf("Textured Shader Error: %s\n", m_shader.getLastError());
		system("pause");
		return false;
	}
	if (m_phongShader.link() == false)
	{
		printf("Phong Shader Error: %s\n", m_shader.getLastError());
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


	if (m_dragonMesh.load("./models/stanford/Dragon.obj", true, true) == false)
	{
		printf("Dragon Mesh Error!\n");
		system("pause");
		return false;
	}

	m_dragonTransform = 
	{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
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
	0,0,0,1
	};

	return true;
}

void GraphicsApp::shutdown()
{
	aie::Gizmos::destroy();
	destroyWindow();
}

void GraphicsApp::update(float deltaTime)
{
	// query time since application started
	float time = getTime();
	// rotate light
	m_light.direction = glm::normalize(vec3(glm::cos(time * 2),glm::sin(time * 2), 0));

	m_camera.update(getWindow(), deltaTime);
	
	if (glfwGetKey(getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		quit();
	}
}

void GraphicsApp::draw()
{
	clearScreen();

	auto pvm = m_camera.getProjectionMatrix() * m_camera.getViewMatrix() *  m_quadTransform;

	m_phongShader.bind();

	// bind light 
	m_phongShader.bindUniform("cameraPosition", m_camera.getPosition());
	m_phongShader.bindUniform("AmbientColour", m_ambientLightColour);
	m_phongShader.bindUniform("DiffuseColour", m_light.diffuse);
	m_phongShader.bindUniform("SpecularColour", m_light.specular);
	m_phongShader.bindUniform("LightDirection", m_light.direction);

	pvm = m_camera.getProjectionMatrix() * m_camera.getViewMatrix() * m_soulSpearTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	// bind transforms for lighting
	m_phongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_soulSpearTransform)));
	m_phongShader.bindUniform("ModelMatrix", m_soulSpearTransform);

	//bind texture to specified location
	m_soulSpearTexture.bind(0);

	m_soulSpearMesh.draw();

	pvm = m_camera.getProjectionMatrix() * m_camera.getViewMatrix() * m_dragonTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	m_dragonMesh.draw();

	Gizmos::clear();

	Gizmos::addTransform(glm::mat4(1), 10.0f);

	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	vec4 yellow(1, 1, 0, 1);

	for (int i = 0; i < 21; i++)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);

		Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}

	//Gizmos::addSphere(vec3(0), 3, 8, 8, yellow);

	Gizmos::draw(m_camera.getProjectionMatrix() * m_camera.getViewMatrix());


}
