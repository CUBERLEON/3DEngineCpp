#include "CoreEngine.h"
#include "Game.h"

CoreEngine::CoreEngine(Game* game, float fpsLimit, bool fpsUnlimited)
{
	m_fpsLimit = fpsLimit;
	m_fpsUnlimited = fpsUnlimited;

	m_game = game;
	m_isRunning = false;
}

CoreEngine::~CoreEngine()
{
}

void CoreEngine::createWindow(int width, int height, std::string title)
{
	m_window = new Window(width, height, title);
	m_renderingEngine = new RenderingEngine();
}

void CoreEngine::start()
{
	if (m_isRunning)
		return;

	if (!m_window)
	{
		Debug::error("trying to start CoreEngine when Window wasn't created!");
		return;
	}

	m_game->init();
	m_game->setEngine(this);

	run();
}

void CoreEngine::stop()
{
	if (!m_isRunning)
		return;

	m_isRunning = false;
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

			m_game->input((float)gameTime);
			m_game->update((float)gameTime);
// 			Input.update();
		}

		if (fpsTime >= fpsRefreshTime)
		{
			Debug::info("%.1f fps", frames / fpsTime);
			fpsTime -= fpsRefreshTime;
			frames = 0;
		}

		if (render || m_fpsUnlimited)
		{
// 			m_game->render(m_renderingEngine);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->render();
			glfwPollEvents();
			frames++;
		}
		else 
		{
// 			std::this_thread::sleep_for(std::chrono::nanoseconds(10));
		}
	}

	cleanUp();
}

void CoreEngine::cleanUp()
{
// 	m_game.dispose();
// 	m_renderingEngine.dispose();
// 
// 	Window.dispose();
}