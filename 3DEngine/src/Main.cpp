#include "core/CoreEngine.h"
#include "TestScene.h"

int main()
{
	CoreEngine* engine = new CoreEngine(new TestScene(), 60, true);
	engine->createWindow(1100, 700, "Test");
	engine->start();
}