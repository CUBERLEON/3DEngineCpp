// #pragma once

#include "Node.h"
#include "CoreEngine.h"
#include "../rendering/RenderingEngine.h"

class Game
{
private:
	Node* m_root;

public:
	Game();
	~Game();

	void init() {}
	void input(float time);
	void update(float time);
	void render(RenderingEngine* renderingEngine);

	void setEngine(CoreEngine* engine);

	Node* getRoot() { return m_root; }
};

