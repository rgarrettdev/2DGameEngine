#include <iostream>
#include "./Definitions.h"
#include "./Engine.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/ControlComponent.h"
#include "./Components/ColliderComponent.h"
#include "./Components/UiTextComponent.h"
#include "./Components/ProjectileComponent.h"
#include "./Map.h"
#include <glm.hpp>
#include <sol.hpp>


EntityManager manager;
AssetManager* Engine::assetManager = new AssetManager(&manager); //Instationating the static asset manager
SDL_Renderer* Engine::renderer;
SDL_Event Engine::event;
Map* map;
SDL_Rect Engine::camera = {0,0,WINDOW_WIDTH,WINDOW_HEIGHT};

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
	if (TTF_Init() !=0)
	{
		std::cerr << "Error intialosing SDL TTF. SDL TTF ERROR: " << TTF_GetError() << std::endl;
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

void Engine::HandleCamera() {

	camera.x = camera.x < 0 ? 0 : camera.x;
	camera.y = camera.y < 0 ? 0 : camera.y;
	camera.x = camera.x > camera.w ? camera.w : camera.x; //Clamping the values of the camera to the tile map
	camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Engine::CheckCollisions() {
	CollisionType collisionType = manager.CheckCollisions();
	if (collisionType == PLAYER_ENEMY_COLLISION)
	{
		ProcessGameOver();
	}
	if (collisionType == PLAYER_LEVEL_COMPLETE_COLLISION)
	{
		ProcessNextLevel(1);
	}
	if (collisionType == PLAYER_PROJECTILE_COLLISION)
	{
		ProcessGameOver();
	}
}

void Engine::ProcessGameOver() {
	std::cout << "Game Over" << std::endl;
	isRunning = false;
}

void Engine::ProcessNextLevel(int levelNumber) {
	std::cout << "Next Level" << std::endl;
	isRunning = false;
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

	HandleCamera();
	CheckCollisions(); //Check if entites are colliding.
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
	//ALL THIS WILL BE LOADED VIA Lua SCRIPT!!
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

	std::string levelName = "Level" + std::to_string(levelNumber);
	lua.script_file("./assets/scripts/" + levelName + ".lua");

	/*************************************************************************************/
	/*						LOADS ASSETS FROM LUA SCRIPT.								 */
	/*************************************************************************************/
	sol::table levelData = lua[levelName];
	sol::table levelAssets = levelData["assets"];
	unsigned int assetIndex = 0;
	while (true)
	{
		sol::optional<sol::table> existsAssetNode = levelAssets[assetIndex];
		if (existsAssetNode == sol::nullopt) //Try to read table, if null then break.
		{
			break;
		}
		else
		{
			sol::table asset = levelAssets[assetIndex];
			std::string assetType = asset["type"];
			if (assetType.compare("texture") == 0)
			{
				std::string assetID = asset["id"];
				std::string assetFile = asset["file"];
				assetManager->AddTexture(assetID, assetFile.c_str());
			}
		}
		assetIndex++;
	}

	/*************************************************************************************/
	/*						LOADS MAP FROM LUA SCRIPT.								     */
	/*************************************************************************************/

	sol::table levelMap = levelData["map"];
	std::string mapTextureID = levelMap["textureAssetID"];
	std::string mapFile = levelMap["file"];

	map = new Map(mapTextureID, static_cast<int>(levelMap["scale"]), static_cast<int>(levelMap["tileSize"]));
	map->LoadMap(mapFile, static_cast<int>(levelMap["mapSizeX"]), static_cast<int>(levelMap["mapSizeY"]));
}