#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Engine
{
public:
	Engine(); //Consturctor
	~Engine(); //Destructor
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
