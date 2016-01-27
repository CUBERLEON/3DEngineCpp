#include "RenderingEngine.h"

#include "../core/Debug.h"
#include "../components/Camera.h"
#include "../components/Light.h"
#include "../rendering/shaders/Shader.h"
#include "../core/Node.h"
#include "../rendering/Window.h"

RenderingEngine::RenderingEngine(Window* window)
: m_window(window)
{
	Debug::info("OpenGL version " + getOpenGLVersion());

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_DEPTH_CLAMP);

	glEnable(GL_TEXTURE_2D);
// 	glEnable(GL_DITHER);

	glDepthFunc(GL_LEQUAL);

// 	glEnable(GL_MULTISAMPLE);

	//sampler2D GLSL locations
	addInteger("diffuse", 0);
	addInteger("normalMap", 1);

	m_ambientShader = new Shader("forward-ambient");
	addVector3f("ambientLight", glm::vec3(0.03f, 0.03f, 0.03f));
}

RenderingEngine::~RenderingEngine()
{
// 	if (m_ambientShader != null)
// 		m_ambientShader.dispose();
}

void RenderingEngine::render(Node* root)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	root->render(m_ambientShader, this);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
// 	glDepthMask(GL_FALSE);

	for (Light* light : m_lights) {
		m_activeLight = light;
 		root->render(light->getShader(), this);
	}

// 	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	m_window->refresh();
}

std::string RenderingEngine::getOpenGLVersion()
{
	return std::string((char*)glGetString(GL_VERSION));
}

Camera* RenderingEngine::getMainCamera()
{
	if (m_mainCamera == nullptr)
		Debug::fatalError("there is no Camera in the scene graph");

	return m_mainCamera;
}

void RenderingEngine::addCamera(Camera* mainCamera)
{
	m_mainCamera = mainCamera;
}

Light* RenderingEngine::getActiveLight()
{
	return m_activeLight;
}

void RenderingEngine::addLight(Light* light)
{
	m_lights.push_back(light);
}
