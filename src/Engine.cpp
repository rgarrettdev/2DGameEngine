#include <iostream>
#include "./Definitions.h"
#include "./Engine.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "Components/ControlComponent.h"
#include "./Map.h"
#include <glm.hpp>

EntityManager manager;
AssetManager* Engine::assetManager = new AssetManager(&manager); //Instationating the static asset manager
SDL_Renderer* Engine::renderer;
SDL_Event Engine::event;
Map* map;

Engine::Engine()
{
	this->isRunning = false;
	this->window = NULL;
	this->ticksLastFrame = 0;
}

Engine::~Engine()
{
}

bool Engine::IsRunning() const
{
	return this->isRunning;
}

void Engine::Init(int width, int height)
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

	LoadLevel(0);
	manager.ListAllEntities();

	isRunning = true;
	return;
}

void Engine::Update()
{	/**Loop is used to allow the program to wait until ~16ms has ellapsed since last frame.
	This is important check on faster hardware, as it could of updated the game in less than ~16ms**/
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TIME_TARGET));

	// deltaTime equals the difference in ticks from the last frame converted to seconds.
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

	//This sets a maximun value for deltaTime, useful when using breakpoints for debugging.
	deltaTime = (deltaTime > 0.05F) ? 0.05f : deltaTime;

	//Sets the ticks for the current frame to be used in the next call.
	ticksLastFrame = SDL_GetTicks(); //SDL_GetTicks returns the time in miliseconds from calling of the function SDL_Init.

	//Cascades to update all entities and all their components.
	manager.Update(deltaTime);


}
void Engine::Render()
{
	/*This funtion clears the back buffer, it then draws all the game objects.
	Finally it swaps the front and back buffer. This is called Double Buffering*/

	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255); //Set background colour.
	SDL_RenderClear(renderer); //Clear the backbuffer.

	if (manager.HasNoEntities()) //Check to see if there are any entities.
	{
		return;
	}
	// Call manager.render to render all enitites and all their components.
	manager.Render();

	SDL_RenderPresent(renderer); //Swap front and back buffers.
}
void Engine::Input()
{
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

void Engine::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Engine::LoadLevel(int levelNumber) {
	
	//include new assets to the assetmanager list.
	//assetManager->AddTexture("mario-image", std::string ("./assets/images/mario.png").c_str()); //How to add a texture to the asset manager
	assetManager->AddTexture("player-image", std::string("./assets/images/spritesheet.png").c_str());
	assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
	//include entities and componenets.
	assetManager->AddTexture("tilemap", std::string("./assets/tilemaps/tilemap.png").c_str());

	map = new Map("tilemap", 2, 16);
	map->LoadMap("./assets/tilemaps/testmap.map", 25, 20);

	Entity& playerEntity(manager.AddEntity("Player", PLAYER_LAYER));
	// Args = position height, position  width, velocity y, velocity  x, image height, image width, scale.
	playerEntity.AddComponent<TransformComponent>(240, 160, 0, 0, 48, 48, 1); 
	// Args = id of asset, int number of Frames to render then loop, int animation playback speed, bool hasDirectionional animations, bool isFixed to a single point.
	playerEntity.AddComponent<SpriteComponent>("player-image", 6, 90, true, false);
	playerEntity.AddComponent<ControlComponent>("w", "s", "a", "d", "space");

	Entity& tankEntity(manager.AddEntity("Tank", ENEMY_LAYER));
	tankEntity.AddComponent<TransformComponent>(0, 0, 10, 10, 32, 32, 1);
	tankEntity.AddComponent<SpriteComponent>("tank-image");
}
