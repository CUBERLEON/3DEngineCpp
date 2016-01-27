#include "Component.h"

#include "../core/Debug.h"
#include "../core/Node.h"
#include "../core/Transform.h"
#include "../core/CoreEngine.h"
#include "../core/Input.h"
#include "../rendering/Window.h"

Component::Component()
{
	m_node = nullptr;
}

Component::~Component()
{
}

Transform* Component::getTransform() const
{
	Node* node; Transform* transform = nullptr;
	if ((node = getNode()) == nullptr || (transform = node->getTransform()) == nullptr)
		Debug::warning("NULL returned while executing Component.getTransform()");
	return transform;
}

Window* Component::getWindow() const
{
	Node* node; CoreEngine* coreEngine; Window* window = nullptr;
	if ((node = getNode()) == nullptr || (coreEngine = node->getCoreEngine()) == nullptr || (window = coreEngine->getWindow()) == nullptr)
		Debug::warning("NULL returned while executing Component.getWindow()");
	return window;
}

Input* Component::getInput() const
{
	Window* window; Input* input = nullptr;
	if ((window = getWindow()) == nullptr || (input = window->getInput()) == nullptr)
		Debug::warning("NULL returned while executing Component.getInput()");
	return input;
}

Node* Component::getNode() const
{
	if (m_node == nullptr)
		Debug::warning("NULL returned while executing Component.getNode() (Node wasn't assigned)");
	return m_node;
}
