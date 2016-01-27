#ifndef CORE_ENGINE_H
#define CORE_ENGINE_H

#include <string>

class Scene;
class RenderingEngine;
class Window;

class CoreEngine 
{
public:
	CoreEngine(Scene* game, float fpsLimit, bool fpsUnlimited);
	~CoreEngine();

	void createWindow(int width, int height, const std::string& title);

	void start();
	void stop();

	inline float getFpsLimit() const { return m_fpsLimit; }
	inline void setFpsLimit(float val) { m_fpsLimit = val; }
	inline bool isFpsUnlimited() const { return m_fpsUnlimited; }
	inline void setFpsUnlimited(bool val) { m_fpsUnlimited = val; }

	RenderingEngine* getRenderingEngine() const;
	Window* getWindow() const;
protected:
private:
	float m_fpsLimit;
	bool m_fpsUnlimited;

	RenderingEngine* m_renderingEngine;
	Window* m_window;
	Scene* m_scene;

	bool m_isRunning;

	void run();
};
#endif // CORE_ENGINE_H