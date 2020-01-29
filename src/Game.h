#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Game
{
public:
	Game(); //Consturctor
	~Game(); //Destructor
	bool IsRunning() const;
	void Init(int width, int height);
	void Input();
	void Update();
	void Render();
	void Destroy();

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int ticksLastFrame;
};
#endif
