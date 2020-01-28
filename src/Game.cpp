#include <iostream>
#include "Definitions.h"
#include "Game.h"

Game::Game()
{
	this->isRunning = false;
	this->renderer = NULL;
	this->window = NULL;
}

Game::~Game()
{
}

bool Game::IsRunning() const
{
	return this->isRunning;
}

float projectilePosX = 0.0f; //Temporary object for renderering
float projectilePosY = 0.0f; //Temporary object for renderering
float projectileVelX = 30.0f; //Temporary object for renderering
float projectileVelY = 30.0f; //Temporary object for renderering

void Game::Init(int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Error initialising SDL. SDL ERROR: " << SDL_GetError() << std::endl;
		return;
	}
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_BORDERLESS
	);
	if (!window) //Check if window was created.
	{
		std::cerr << "Error initialising SDL. SDL ERROR: " << SDL_GetError() << std::endl;
		return;
	}
	renderer = SDL_CreateRenderer(window, -1, 0); // -1 sets the default display to be the traget of the renderer.
	if (!renderer) //Check if renderer was created.
	{
		std::cerr << "Error initialising SDL. SDL ERROR: " << SDL_GetError() << std::endl;
		return;
	}

	isRunning = true;
	return;
}

void Game::Update()
{	/**Loop is used to allow the program to wait until ~16ms has ellapsed since last frame.
	This is important check on faster hardware, as it could of updated the game in less than ~16ms**/
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TIME_TARGET));

	// deltaTime equals the difference in ticks from the last frame converted to seconds.
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

	//This sets a maximun value for deltaTime, useful when using breakpoints for debugging.
	deltaTime = (deltaTime > 0.05F) ? 0.05f : deltaTime;

	//Sets the ticks for the current frame to be used in the next call.
	ticksLastFrame = SDL_GetTicks(); //SDL_GetTicks returns the miliseconds from calling SDL_Init.

	projectilePosX += projectileVelX * deltaTime;
	projectilePosY += projectileVelY * deltaTime;
}
void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer); //Clear the backbuffer

	SDL_Rect projectile //SDL_Rect is a struct with the definition of a rectangle.
	{
		(int)projectilePosX,	//Cast int since we are using pixels.
		(int)projectilePosY,    //Cast int since we are using pixels.
		10,
		10
	};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &projectile);
	SDL_RenderPresent(renderer);
}
void Game::Input()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT: {
		isRunning = false;
		break;
	}
	case SDL_KEYDOWN: {
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			isRunning = false;
		}
	}
	default:
		break;
	}
}

void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}