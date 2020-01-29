#include <iostream>
#include <SDL.h>
#include "src/Definitions.h"
#include "src/Engine.h"

int main(int argc, char* argv[])
{
	Engine* engine = new Engine();

	engine->Init(WINDOW_WIDTH, WINDOW_HEIGHT);

	while (engine->IsRunning())
	{
		engine->Input();
		engine->Update();  //Game loop
		engine->Render();
	}

	engine->Destroy();

	return 0;
}