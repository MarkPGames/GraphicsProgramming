#include "Application.h"
#include "gl_core_4_4.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

Application::Application()
	: m_window(nullptr),
	m_gameOver(false),
	m_fps(0) {
}

Application::~Application() {
}

bool Application::createWindow(const char* title, int width, int height, bool fullscreen) {

	if (glfwInit() == GL_FALSE)
		return false;

	m_window = glfwCreateWindow(width, height, title, (fullscreen ? glfwGetPrimaryMonitor() : nullptr), nullptr);
	if (m_window == nullptr) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return false;
	}

	glfwSetWindowSizeCallback(m_window, [](GLFWwindow*, int w, int h) { glViewport(0, 0, w, h); });

	glClearColor(0, 0, 0, 1);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glEnable(GL_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

void Application::destroyWindow() 
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Application::run(const char* title, int width, int height, bool fullscreen) 
{

	// start game loop if successfully initialised
	if (createWindow(title, width, height, fullscreen) &&
		startup()) {

		// variables for timing
		double prevTime = glfwGetTime();
		double currTime = 0;
		m_deltaTime = 0;
		unsigned int frames = 0;
		double fpsInterval = 0;

		// loop while game is running
		while (!m_gameOver) {

			// update delta time
			currTime = glfwGetTime();
			m_deltaTime = currTime - prevTime;
			prevTime = currTime;

			// update window events (input etc)
			glfwPollEvents();

			// skip if minimised
			if (glfwGetWindowAttrib(m_window, GLFW_ICONIFIED) != 0)
				continue;

			// update fps every second
			frames++;
			fpsInterval += m_deltaTime;
			if (fpsInterval >= 1.0f) {
				m_fps = frames;
				frames = 0;
				fpsInterval -= 1.0f;
			}

			update(float(m_deltaTime));

			draw();

			//present backbuffer to the monitor
			glfwSwapBuffers(m_window);

			// should the game exit?
			m_gameOver = m_gameOver || glfwWindowShouldClose(m_window) == GLFW_TRUE;
		}
	}

	// cleanup
	shutdown();
	destroyWindow();
}

bool Application::hasWindowClosed() {
	return glfwWindowShouldClose(m_window) == GL_TRUE;
}

void Application::clearScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Application::setBackgroundColour(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

void Application::setVSync(bool enable) {
	glfwSwapInterval(enable ? 1 : 0);
}

void Application::setShowCursor(bool visible) {
	ShowCursor(visible);
}

unsigned int Application::getWindowWidth() const {
	int w = 0, h = 0;
	glfwGetWindowSize(m_window, &w, &h);
	return w;
}

unsigned int Application::getWindowHeight() const {
	int w = 0, h = 0;
	glfwGetWindowSize(m_window, &w, &h);
	return h;
}

float Application::getTime() const {
	return (float)glfwGetTime();
}

float Application::getDeltaTime()
{
	return m_deltaTime;
}

GLFWwindow* Application::getWindow()
{
	return m_window;
}