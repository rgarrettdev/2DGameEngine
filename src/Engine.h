#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "./EntityManager.h"

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
	static SDL_Renderer* renderer; //Allows components to access the renderer.
	void LoadLevel(int levelNumber);
	void PrintEntites();

private:
	bool isRunning;
	SDL_Window* window;
	int ticksLastFrame;
};
#endif