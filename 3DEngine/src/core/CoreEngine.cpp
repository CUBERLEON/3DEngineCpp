#include "CoreEngine.h"

#include <chrono>
#include <thread>

#include "../rendering/RenderingEngine.h"
#include "../rendering/Window.h"
#include "Scene.h"
#include "Debug.h"
#include "Time.h"

CoreEngine::CoreEngine(Scene* scene, float fpsLimit, bool fpsUnlimited) : 
m_fpsLimit(fpsLimit), m_fpsUnlimited(fpsUnlimited), m_scene(scene), m_isRunning(false)
{
}

CoreEngine::~CoreEngine()
{
// 	m_game.dispose();
// 	m_renderingEngine.dispose();
// 
// 	Window.dispose();
}

void CoreEngine::createWindow(int width, int height, const std::string& title)
{
	m_window = new Window(width, height, title);
	m_renderingEngine = new RenderingEngine(m_window);
}

void CoreEngine::start()
{
	if (m_isRunning)
		return;

	if (!m_window)
	{
		Debug::error("trying to start CoreEngine when Window wasn't created");
		return;
	}

	m_scene->setCoreEngine(this);
	m_scene->init();

	run();
}

void CoreEngine::stop()
{
	if (!m_isRunning)
		return;

	m_isRunning = false;
}

RenderingEngine* CoreEngine::getRenderingEngine() const
{
	if (m_renderingEngine == nullptr)
		Debug::warning("NULL returned while executing CoreEngine.getRenderingEngine()");
	return m_renderingEngine;
}

Window* CoreEngine::getWindow() const
{
	if (m_window == nullptr)
		Debug::warning("NULL returned while executing CoreEngine.getWindow()");
	return m_window;
}

void CoreEngine::run()
{
	m_isRunning = true;

	int frames = 0;
	double fpsTime = 0;
	double fpsRefreshTime = 1.0;

	double startTime = Time::getTime();
	double frameTime = 1.0 / m_fpsLimit;
	double unprocessedTime = 0;

	while (m_isRunning)
	{
		if (m_window->isCloseRequested())
			stop();

		double endTime = Time::getTime();
		double passedTime = endTime - startTime;
		startTime = endTime;

		unprocessedTime += passedTime;
		fpsTime += passedTime;

		bool render = false;

		if (unprocessedTime >= frameTime)
		{
			double gameTime = frameTime * (int)floor(unprocessedTime / frameTime);
			unprocessedTime -= gameTime;

			render = true;

			m_scene->input((float)gameTime);
			m_scene->update((float)gameTime);
		}

		if (fpsTime >= fpsRefreshTime)
		{
			Debug::info("%.1f fps", frames / fpsTime);
			fpsTime -= fpsRefreshTime;
			frames = 0;
		}

		if (render || m_fpsUnlimited)
		{
			m_scene->render(m_renderingEngine);
			frames++;
		}
		else 
		{
			std::this_thread::sleep_for(std::chrono::nanoseconds(10));
		}
	}
}