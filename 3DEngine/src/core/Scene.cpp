#include "Scene.h"

#include "../core/Debug.h"
#include "CoreEngine.h"
#include "../rendering/RenderingEngine.h"
#include "../rendering/Window.h"
#include "Node.h"

Scene::Scene()
{
	m_root = new Node();
}

Scene::~Scene()
{
 	delete m_root;
}

void Scene::input(float time)
{
	m_root->input(time);
}

void Scene::update(float time)
{
	m_root->update(time);
}

void Scene::render(RenderingEngine* renderingEngine)
{
	renderingEngine->render(m_root);
}

void Scene::setCoreEngine(CoreEngine* engine)
{
	m_root->setCoreEngine(engine);
}

Node* Scene::getRoot()
{
	return m_root;
}