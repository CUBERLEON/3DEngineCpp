#pragma once

#include <string>
#include <chrono>
#include <thread>

#include "../rendering/RenderingEngine.h"
#include "../rendering/Window.h"
#include "Debug.h"
#include "Time.h"

class Game;

class CoreEngine 
{
private:
	float m_fpsLimit;
	bool m_fpsUnlimited;

	Window* m_window;
	RenderingEngine* m_renderingEngine;
	Game* m_game;
	bool m_isRunning;

	void run();
	void cleanUp();

public:
	CoreEngine(Game* game, float fpsLimit, bool fpsUnlimited);
	~CoreEngine();

	void createWindow(int width, int height, std::string title);

	void start();
	void stop();

	inline float getFpsLimit() const { return m_fpsLimit; }
	inline void setFpsLimit(float val) { m_fpsLimit = val; }
	inline bool isFpsUnlimited() const { return m_fpsUnlimited; }
	inline void setFpsUnlimited(bool val) { m_fpsUnlimited = val; }
// 	RenderingEngine getRenderingEngine() const { return m_renderingEngine; }
};