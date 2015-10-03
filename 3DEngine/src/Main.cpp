#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "core/CoreEngine.h"
#include "core/Game.h"

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
// 	glfwSetErrorCallback(error_callback);
// 	glfwSetKeyCallback(window, key_callback);

	CoreEngine* engine = new CoreEngine(new Game(), 60, false);
	engine->createWindow(800, 600, "Test");
	engine->start();
}