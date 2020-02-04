#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "./EntityManager.h"

class AssetManager;

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
	static AssetManager* assetManager;
	static SDL_Event event;
	static SDL_Rect camera; //allows this to be called across the program. used in tile component and sprite component.
	void LoadLevel(int levelNumber);
	void HandleCamera();
	void CheckCollisions();
	void ProcessGameOver();
	void ProcessNextLevel(int levelNumber);

private:
	bool isRunning;
	SDL_Window* window;
	int ticksLastFrame;
};
#endif
