#include "core/CoreEngine.h"
#include "TestScene.h"

int main()
{
	CoreEngine* engine = new CoreEngine(new TestScene(), 60, true);
	engine->createWindow(800, 600, "Test");
	engine->start();
}