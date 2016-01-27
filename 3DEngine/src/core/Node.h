#ifndef NODE_H
#define NODE_H

#include <vector>
#include <map>

class CoreEngine;
class Component;
class Transform;
class Shader;
class RenderingEngine;

class Node
{
public:
	Node();
	~Node();

	Node* addComponent(Component* component);
// 	template <typename... Comp>
// 	Node addComponents(Comp... components);

	Node* addComponents(std::vector<Component*>& components);

// 	<Type> Type getComponent(Class<Type> componentClass) {
// 		if (componentClass == null)
// 			return null;
// 
// 		return componentClass.cast(m_componentsMap.get(componentClass.getName()).get());
// 	}

	inline std::vector<Component*> getComponents() const { return m_components; }

// 	<Type> Node removeComponent(Class<Type> componentClass) {
// 		if (m_componentsMap.containsKey(componentClass.getName())) {
// 			m_components.remove(m_componentsMap.get(componentClass.getName()).get());
// 			m_componentsMap.remove(componentClass.getName());
// 		}
// 
// 		return this;
// 	}

// 	Node removeComponent(Component component) {
// 		if (m_componentsMap.containsKey(component.getClass().getName())) {
// 			m_components.remove(component);
// 			m_componentsMap.remove(component.getClass().getName());
// 		}
// 
// 		return this;
// 	}

	Node* addChild(Node* child);

// 	Node addChildren(Node... children) {
// 		for (Node child : children) {
// 			addChild(child);
// 		}
// 		return this;
// 	}

	Node* addChildren(std::vector<Node*> children);

// 	Node getChildByName(std::string name) {
// 		return m_childrenMap.get(name).get();
// 	}

	inline std::vector<Node*> getChildren() const { return m_children; }

// 	Node removeChildByName(std::string name) {
// 		if (m_childrenMap.containsKey(name)) {
// 			Node child = m_childrenMap.get(name).get();
// 			if (child != null) {
// 				child.dispose();
// 				m_children.remove(child);
// 			}
// 			m_childrenMap.remove(name);
// 		}
// 
// 		return this;
// 	}

// 	Node removeChild(Node child) {
// 		if (child != null && m_childrenMap.containsKey(child.getName())) {
// 			child.dispose();
// 			m_children.remove(child);
// 			m_childrenMap.remove(child.getName());
// 		}
// 
// 		return this;
// 	}

// 	inline std::string getName() { return m_name; }
	Transform* getTransform() const { return m_transform; };
	Node* getParent() const { return m_parent; }
protected:
private:
	Node* m_parent;

	CoreEngine* m_coreEngine;

	std::vector<Node*> m_children;
// 	std::map<std::std::string, Node*> m_childrenMap;

	std::vector<Component*> m_components;
// 	std::map<std::std::string, Component*> m_componentsMap;

	Transform* m_transform;

// 	std::std::string m_name;
friend class RenderingEngine;
friend class Scene;
friend class Component;

	void input(float time);
	void update(float time);
	void render(Shader* shader, RenderingEngine* renderingEngine);

	void setCoreEngine(CoreEngine* engine);
	CoreEngine* getCoreEngine() const { return m_coreEngine; }
	inline void setParent(Node* parent) { m_parent = parent; }
};

#endif // NODE_H
