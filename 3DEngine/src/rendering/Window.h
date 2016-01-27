#pragma once

#include <string>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

class Input;

class Window
{
public:
	Window(int width, int height, std::string title);
	~Window();

	void refresh();
	void resize(int width, int height);

	bool isCloseRequested();
	bool isCreated();

	int getWidth();
	int getHeight();

	std::string getTitle();
	glm::vec2 getCenter();

	Input* getInput();
	GLFWwindow* getGLFWwindow();

	void moveToScreenCenter();
protected:
private:
	GLFWwindow* m_glfwWindow;
	Input* m_input;

	std::string m_title;
};

