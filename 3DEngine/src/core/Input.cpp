#include "Input.h"

#include "../rendering/Window.h"

Input::Input(Window* window)
: m_window(window)
{
// 	glfwSetInputMode(m_window->getGLFWwindow(), GLFW_STICKY_KEYS, 1);
}

Input::~Input()
{
}

int Input::getKey(int keyCode) const
{
	return glfwGetKey(m_window->getGLFWwindow(), keyCode);
}

int Input::getMouseButton(int keyCode) const
{
	return glfwGetMouseButton(m_window->getGLFWwindow(), keyCode);
}

glm::vec2 Input::getMousePosition() const
{
	double posx, posy;
	glfwGetCursorPos(m_window->getGLFWwindow(), &posx, &posy);
	return glm::vec2((float)posx, (float)posy);
}

void Input::setCursor(bool value) const
{
	glfwSetInputMode(m_window->getGLFWwindow(), GLFW_CURSOR, value ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}

void Input::setMousePosition(const glm::vec2& pos) const
{
	glfwSetCursorPos(m_window->getGLFWwindow(), pos.x, pos.y);
}
