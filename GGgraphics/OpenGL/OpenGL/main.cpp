#include "GraphicsApp.h"

int main()
{
	////make window
	//if (glfwInit() == false)
	//{
	//	return -1;
	//}
	//
	//GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);
	//
	//if (window == nullptr)
	//{
	//	glfwTerminate();
	//	return -2;
	//}
	//
	//glfwMakeContextCurrent(window);
	//
	//if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	//{
	//	glfwDestroyWindow(window);
	//	glfwTerminate();
	//	return -3;
	//}

	////Startup
	//Gizmos::create(1000, 1000, 1000, 1000);
	//
	//mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	//mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
	//
	//auto major = ogl_GetMajorVersion();
	//auto minor = ogl_GetMinorVersion();
	//printf("GL: %i.%i\n", major, minor);
	//
	//glClearColor(0.5f, 1.0f, 1.0f, 1);
	//glEnable(GL_DEPTH_TEST); // enables the depth buffer
	//
	//float value = 0;
	//
	////update
	//
	//while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	//{
	//	//wipe back buffer			clear the dist to closest pixels
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//
	//	// game logice and update
	//
	//	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	//	{
	//		value+= 2;
	//		view = glm::lookAt(vec3(value, value, value), vec3(0), vec3(0, 1, 0));
	//	}
	//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	{
	//		value -= 2;
	//		view = glm::lookAt(vec3(value, value, value), vec3(0), vec3(0, 1, 0));
	//	}
	//
	//	//DRAW
	//	//render code
	//
	//	//Gizmo Rendering
	//	Gizmos::clear();
	//
	//	Gizmos::addTransform(glm::mat4(1));
	//
	//	vec4 white(1);
	//	vec4 black(0, 0, 0, 1);
	//
	//	for (int i = 0; i < 21; i++)
	//	{
	//		Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);
	//
	//		Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
	//	}
	//
	//	Gizmos::draw(projection * view);
	//
	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//}
	//
	////shutdown
	//aie::Gizmos::destroy();
	//glfwDestroyWindow(window);
	//glfwTerminate();

	// allocation
	auto app = new GraphicsApp();

	// initialise and loop
	app->run("GraphicsApp", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}