#include "Window.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

Window::Window(int width, int height, std::string title)
{
	if (!glfwInit())
		Debug::fatalError("glfw initialization failed");

	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	if (!m_window) {
		glfwTerminate();
		Debug::fatalError("creation of Window failed");
	}

	glfwMakeContextCurrent(m_window);
	glfwSetKeyCallback(m_window, key_callback);

	GLenum err = glewInit();
	if (err != GLEW_OK)
		Debug::fatalError("%s", glewGetErrorString(err));

	m_title = title;
	Debug::info("Window '" + title + "' (" + std::to_string(width) + "x" + std::to_string(height) + ") was successfully created");
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Window::render()
{
	if (isCreated())
	{
		glfwSwapBuffers(m_window);
	}
}

bool Window::isCloseRequested()
{
	return glfwWindowShouldClose(m_window) != 0;
}

bool Window::isCreated()
{
	return m_window != nullptr;
}

int Window::getWidth()
{
	int width, height;
	glfwGetWindowSize(m_window, &width, &height);
	return width;
}

int Window::getHeight()
{
	int width, height;
	glfwGetWindowSize(m_window, &width, &height);
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

void Window::resize(int width, int height)
{
	glfwSetWindowSize(m_window, width, height);
}
