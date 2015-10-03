#pragma once

#include <string>
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "glm.hpp"

#include "../core/Debug.h"

class Window
{
private:
	GLFWwindow* m_window;
	std::string m_title;

public:
	Window(int width, int height, std::string title);
	~Window();

	void render();
	bool isCloseRequested();
	bool isCreated();

	int getWidth();
	int getHeight();
	std::string getTitle();
	glm::vec2 getCenter();

	void resize(int width, int height);
};

