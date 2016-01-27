#include "Window.h"

#include "../core/Debug.h"
#include "../core/Input.h"

Window::Window(int width, int height, std::string title) : m_title(title)
{
	if (!glfwInit())
		Debug::fatalError("glfw initialization failed");

	glfwWindowHint(GLFW_SAMPLES, 4);
	m_glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	if (!m_glfwWindow)
	{
		glfwTerminate();
		Debug::fatalError("creation of Window failed");
	}

	glfwMakeContextCurrent(m_glfwWindow);
	moveToScreenCenter();
	m_input = new Input(this);
	m_input->setCursor(false);

	GLenum err = glewInit();
	if (err != GLEW_OK)
		Debug::fatalError("%s", glewGetErrorString(err));

	Debug::info("Window '" + title + "' (" + std::to_string(width) + "x" + std::to_string(height) + ") was created");
}

Window::~Window()
{
	Debug::info("Window destructor");
	glfwDestroyWindow(m_glfwWindow);
	glfwTerminate();
}

void Window::refresh()
{
	if (isCreated())
	{
		glfwSwapBuffers(m_glfwWindow);
		glfwPollEvents();
	}
}

void Window::resize(int width, int height)
{
	glfwSetWindowSize(m_glfwWindow, width, height);
}

bool Window::isCloseRequested()
{
	return glfwWindowShouldClose(m_glfwWindow) != 0;
}

bool Window::isCreated()
{
	return m_glfwWindow != nullptr;
}

int Window::getWidth()
{
	int width, height;
	glfwGetWindowSize(m_glfwWindow, &width, &height);
	return width;
}

int Window::getHeight()
{
	int width, height;
	glfwGetWindowSize(m_glfwWindow, &width, &height);
	return height;
}

std::string Window::getTitle()
{
	return m_title;
}

glm::vec2 Window::getCenter()
{
	return glm::vec2(getWidth() / 2, getHeight() / 2);
}

Input* Window::getInput()
{
	return m_input;
}

GLFWwindow* Window::getGLFWwindow()
{
	return m_glfwWindow;
}

void Window::moveToScreenCenter()
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	int width, height;
	glfwGetWindowSize(m_glfwWindow, &width, &height);
	glfwSetWindowPos(m_glfwWindow, (mode->width - width) / 2, (mode->height - height) / 2);
}

// static void error_callback(int error, const char* description)
// {
// 	fputs(description, stderr);
// 	_fgetchar();
// }
// 	glfwSetErrorCallback(error_callback);