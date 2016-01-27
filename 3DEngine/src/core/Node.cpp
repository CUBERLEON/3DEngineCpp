#include "Node.h"

#include "Debug.h"
#include "Transform.h"
#include "../components/Component.h"

Node::Node()
{
	m_coreEngine = nullptr;
	m_transform = new Transform();
// 	m_name = name;
}

Node::~Node()
{
// 	for (Component component : m_components)
// 		component.dispose();
// 
// 	for (Node child : m_children)
// 		child.dispose();
}

Node* Node::addComponent(Component* component)
{
	m_components.push_back(component);
	component->setNode(this);
// 	if (m_componentsMap.containsKey(component.getClass().getName()))
// 		Debug.error("cannot add second " + component.getClass().getName() + " Component to the Node('" + m_name + "')");
// 	else {
// 		component.setNode(this);
// 
// 		m_componentsMap.put(component.getClass().getName(), new WeakReference<>(component));
// 		m_components.add(component);
// 	}

	return this;
}

Node* Node::addComponents(std::vector<Component*>& components)
{
	for (Component* component : components) 
		addComponent(component);

	return this;
}

// template <typename... Comp>
// Node Node::addComponents(Comp... components)
// {
// 	for (Component component : components) {
// 		addComponent(component);
// 	}
// 	return this;
// }

Node* Node::addChild(Node* child)
{
	m_children.push_back(child);
	child->setParent(this);
	child->getTransform()->setParent(m_transform);
	child->setCoreEngine(m_coreEngine);
// 	if (m_childrenMap.containsKey(child.getName()))
// 		Debug.error("cannot add second Node('" + child.getName() + "') to the Node('" + m_name + "')");
// 	else {
// 		child.setParent(this);
// 		child.getTransform().setParent(m_transform);
// 		child.setEngine(m_engine);
// 
// 		m_childrenMap.put(child.getName(), new WeakReference<>(child));
// 		m_children.add(child);
// 	}

	return this;
}

Node* Node::addChildren(std::vector<Node*> children)
{
	for (Node* child : children) 
	{
		addChild(child);
	}
	return this;
}

void Node::input(float time)
{
	for (Component* component : m_components)
		component->input(time);

	for (Node* child : m_children)
		child->input(time);
}

void Node::update(float time)
{
	m_transform->update();

	for (Component* component : m_components)
		component->update(time);

	for (Node* child : m_children)
		child->update(time);
}

void Node::render(Shader* shader, RenderingEngine* renderingEngine)
{
	for (Component* component : m_components)
		component->render(shader, renderingEngine);

	for (Node* child : m_children)
		child->render(shader, renderingEngine);
}

void Node::setCoreEngine(CoreEngine* engine)
{
	if (engine != m_coreEngine) 
	{
		m_coreEngine = engine;
		for (Component* component : m_components)
			component->addToEngine(engine);

		for (Node* child : m_children)
			child->setCoreEngine(engine);
	}
}