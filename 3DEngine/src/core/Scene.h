#ifndef SCENE_H
#define SCENE_H

class Node;
class RenderingEngine;
class CoreEngine;
class Window;

class Scene
{
	friend class CoreEngine;
public:
	Scene();
	~Scene();

	Node* getRoot();
protected:
private:
	Node* m_root;

	void setCoreEngine(CoreEngine* engine);

	virtual void init() {}
	void input(float time);
	void update(float time);
	void render(RenderingEngine* renderingEngine);
};

#endif // SCENE_H
