#pragma once

#include "GL/glew.h"
#include <glm\glm.hpp>
#include <string>
#include <vector>
#include "Container.h"

class Node;
class Camera;
class Light;
class Shader;
class Window;

class RenderingEngine : public Container
{
public:
	RenderingEngine(Window* window);
	~RenderingEngine();

	void render(Node* root);

	static std::string getOpenGLVersion();

	Camera* getMainCamera();
//    void setMainCamera(Camera mainCamera) {
//        m_mainCamera = mainCamera;
//    }
	void addCamera(Camera* mainCamera);

	Light* getActiveLight();
	void addLight(Light* light);
protected:
private:
	Window* m_window;

	Camera* m_mainCamera;

	std::vector<Light*> m_lights;
	Light* m_activeLight;

	Shader* m_ambientShader;
};

