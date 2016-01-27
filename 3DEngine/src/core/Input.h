#ifndef INPUT_H
#define INPUT_H

#include <glm/glm.hpp>

class Window;
struct GLFWwindow;

class Input
{
public:
	Input(Window* window);
	~Input();

	int getKey(int keyCode) const;

	int getMouseButton(int keyCode) const;
	glm::vec2 getMousePosition() const;
	void setMousePosition(const glm::vec2& pos) const;
	void setCursor(bool value) const;
protected:
private:
	Window* m_window;
};

#endif // INPUT_H
