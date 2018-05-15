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
	Gizmos::create(10000, 10000, 10000, 10000);

	projection = glm::perspective(glm::pi<float>() * 0.25f, (float)getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f);
	m_camera.setProjectionMatrix(projection);

	//load vertex shader from file
	m_shader.loadShader(aie::eShaderStage::VERTEX, "../OpenGL/shaders/simple.vert");
	//load fragment shader from file
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "../OpenGL/shaders/simple.frag");
	if (m_shader.link() == false)
	{
		printf("Shader Error: %s\n", m_shader.getLastError());
		return false;
	}

	m_quadMesh.initialiseQuad();

	//make the quad 10 units wide
	m_quadTransform = {
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

	return true;
}

void GraphicsApp::shutdown()
{
	aie::Gizmos::destroy();
	destroyWindow();
}

void GraphicsApp::update(float deltaTime)
{

	m_camera.update(getWindow(), deltaTime);
	

	if (glfwGetKey(getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		quit();
	}
}

void GraphicsApp::draw()
{
	clearScreen();

	setBackgroundColour(0.0f, 0.0f, 0.0f, 1.0f);

	//bind shader
	m_shader.bind();

	//bind transform
	auto pvm = m_camera.getProjectionMatrix() * m_camera.getViewMatrix() *  m_quadTransform;
	m_shader.bindUniform("ProjectionViewModel", pvm);

	//draw quad
	m_quadMesh.draw();

	Gizmos::clear();

	Gizmos::addTransform(glm::mat4(1), 10.0f);

	vec4 white(1);
	vec4 black(0, 0, 0.5, 1);
	vec4 yellow(1, 1, 0, 1);

	for (int i = 0; i < 21; i++)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);

		Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}

	Gizmos::addSphere(vec3(0), 3, 8, 8, yellow);

	Gizmos::draw(m_camera.getProjectionMatrix() * m_camera.getViewMatrix());


}
