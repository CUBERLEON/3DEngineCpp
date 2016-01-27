#ifndef COMPONENT_H
#define COMPONENT_H

class Transform;
class Node;
class RenderingEngine;
class Shader;
class CoreEngine;
class Window;
class Input;

class Component
{
public:
	Transform* getTransform() const;
	Node* getNode() const;
	Window* getWindow() const;
	Input* getInput() const;
protected:
	Component();
	~Component();
private:
	Node* m_node;

friend class Node;

	virtual void input(float time) {}
	virtual void update(float time) {}
	virtual void render(Shader* shader, RenderingEngine* renderingEngine) {}

	void setNode(Node* node) { m_node = node; }
	virtual void addToEngine(CoreEngine* engine) {}
};

#endif // COMPONENT_H
