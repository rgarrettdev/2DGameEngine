#include <iostream>
#include <SDL.h>
#include "src/Definitions.h"
#include "src/Game.h"

int main(int argc, char* argv[])
{
	Game* game = new Game();

	game->Init(WINDOW_WIDTH, WINDOW_HEIGHT);

	while (game->IsRunning())
	{
		game->Input();
		game->Update();
		game->Render();
	}

	game->Destroy();

	return 0;
}