#include <iostream>
#include "./Definitions.h"
#include "./Engine.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/ControlComponent.h"
#include "./Components/ColliderComponent.h"
#include "./Components/UiTextComponent.h"
#include "./Components/ProjectileComponent.h"
#include "./Components/AudioComponent.h"
#include "./Map.h"
#include <glm.hpp>
#include <sol.hpp>


EntityManager manager;
AssetManager* Engine::assetManager = new AssetManager(&manager); //Instationating the static asset manager
SDL_Renderer* Engine::renderer;
SDL_Event Engine::event;
Map* map;
SDL_Rect Engine::camera = {0,0,WINDOW_WIDTH,WINDOW_HEIGHT};
Entity* player = NULL;

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
		std::cerr << "Error intialising SDL TTF. SDL TTF ERROR: " << TTF_GetError() << std::endl;
		return;
	}
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "Error: " << Mix_GetError() << std::endl;
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

void Engine::LoadLevel(int levelNumber) {
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

	std::string levelName = "Level" + std::to_string(levelNumber);
	/*
	*
	* Checks the lua script for valid syntax
	*
	*/	
	std::string validLua = Engine::CheckValidLua("./assets/scripts/" + levelName + ".lua");
	if (validLua == "PASS")
	{
		lua.script_file("./assets/scripts/" + levelName + ".lua");

		/*
		* LOADS ASSETS FROM LUA SCRIPT.
		*/
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
				if (assetType.compare("font") == 0)
				{
					std::string assetID = asset["id"];
					std::string assetFile = asset["file"];
					int fontSize = asset["fontSize"];
					assetManager->AddFont(assetID, assetFile.c_str(), fontSize);
				}
				if (assetType.compare("sound") == 0)
				{
					std::string assetID = asset["id"];
					std::string assetFile = asset["file"];
					assetManager->AddMusic(assetID, assetFile.c_str());
				}
			}
			assetIndex++;
		}

		/*
		* LOADS MAP FROM LUA SCRIPT.
		*/

		sol::table levelMap = levelData["map"];
		std::string mapTextureID = levelMap["textureAssetID"];
		std::string mapFile = levelMap["file"];

		map = new Map(mapTextureID, static_cast<int>(levelMap["scale"]), static_cast<int>(levelMap["tileSize"]));
		map->LoadMap(mapFile, static_cast<int>(levelMap["mapSizeX"]), static_cast<int>(levelMap["mapSizeY"]));

		/*
		* LOADS ENTITES AND COMPONENTS FROM LUA SCRIPT.
		*/

		sol::table levelEntities = levelData["entities"];
		unsigned int entityIndex = 0;
		while (true)
		{
			sol::optional<sol::table> exisitsEntityNode = levelEntities[entityIndex];
			if (exisitsEntityNode == sol::nullopt)
			{
				break;
			}
			else
			{
				sol::table entity = levelEntities[entityIndex];
				std::string entityName = entity["name"];
				LayerType entityLayer = static_cast<LayerType>(static_cast<int>(entity["layer"]));

				//Add new entity
				auto& newEntity(manager.AddEntity(entityName, entityLayer));

				//Add transform component
				sol::optional<sol::table> existsTransformComponent = entity["components"];
				if (existsTransformComponent != sol::nullopt)
				{
					newEntity.AddComponent<TransformComponent>(
						static_cast<int>(entity["components"]["transform"]["position"]["y"]),
						static_cast<int>(entity["components"]["transform"]["position"]["x"]),
						static_cast<int>(entity["components"]["transform"]["velocity"]["y"]),
						static_cast<int>(entity["components"]["transform"]["velocity"]["x"]),
						static_cast<int>(entity["components"]["transform"]["height"]),
						static_cast<int>(entity["components"]["transform"]["width"]),
						static_cast<int>(entity["components"]["transform"]["scale"])
						);
				}
				//Add sprite component
				sol::optional<sol::table> existsSpriteComponent = entity["components"]["sprite"];
				if (existsSpriteComponent != sol::nullopt)
				{
					std::string textureID = entity["components"]["sprite"]["textureAssetID"];
					bool isAnimated = entity["components"]["sprite"]["animated"];
					if (isAnimated)
					{
						newEntity.AddComponent<SpriteComponent>(
							textureID,
							static_cast<int>(entity["components"]["sprite"]["frameCount"]),
							static_cast<int>(entity["components"]["sprite"]["animationSpeed"]),
							static_cast<bool>(entity["components"]["sprite"]["hasDirections"]),
							static_cast<bool>(entity["components"]["sprite"]["fixed"])
							);
					}
					else
					{
						newEntity.AddComponent<SpriteComponent>(textureID, false);
					}
				}
				//Add input component
				sol::optional<sol::table> existsInputComponent = entity["components"]["input"];
				if (existsInputComponent != sol::nullopt)
				{
					sol::optional<sol::table> existsKeyboardInput = entity["components"]["input"]["keyboard"];
					if (existsKeyboardInput != sol::nullopt)
					{
						std::string upKey = entity["components"]["input"]["keyboard"]["up"];
						std::string downKey = entity["components"]["input"]["keyboard"]["down"];
						std::string leftKey = entity["components"]["input"]["keyboard"]["left"];
						std::string rightKey = entity["components"]["input"]["keyboard"]["right"];
						std::string shootKey = entity["components"]["input"]["keyboard"]["shoot"];

						newEntity.AddComponent<ControlComponent>(upKey, downKey, leftKey, rightKey, shootKey);
					}
				}
				//Add collider component
				sol::optional<sol::table> existsColliderComponent = entity["components"]["collider"];
				if (existsColliderComponent != sol::nullopt)
				{
					std::string colliderTag = entity["components"]["collider"]["tag"];
					newEntity.AddComponent<ColliderComponent>(
						colliderTag,
						static_cast<int>(entity["components"]["transform"]["position"]["x"]),
						static_cast<int>(entity["components"]["transform"]["position"]["y"]),
						static_cast<int>(entity["components"]["transform"]["width"]),
						static_cast<int>(entity["components"]["transform"]["height"])
						);
				}
				//Add PROJECTILE COMPONENT
				sol::optional<sol::table> existsProjectileComponent = entity["components"]["projectileEmitter"];
				if (existsProjectileComponent != sol::nullopt)
				{
					int parentEntityPosX = entity["components"]["transform"]["position"]["x"];
					int parentEntityPosY = entity["components"]["transform"]["position"]["y"];
					int parentEntityWidth = entity["components"]["transform"]["width"];
					int parentEntityHeight = entity["components"]["transform"]["height"];
					int projectileWidth = entity["components"]["projectileEmitter"]["width"];
					int projectileHeight = entity["components"]["projectileEmitter"]["height"];
					int projectileSpeed = entity["components"]["projectileEmitter"]["speed"];
					int projectileRange = entity["components"]["projectileEmitter"]["range"];
					int projectileAngle = entity["components"]["projectileEmitter"]["angle"];
					bool projectileLoop = entity["components"]["projectileEmitter"]["shouldLoop"];
					std::string textureAssetID = entity["components"]["projectileEmitter"]["textureAssetID"];
					Entity& projectile(manager.AddEntity("projectile", PROJECTILE_LAYER)); //Create an entity attached to the parent.
					projectile.AddComponent<TransformComponent>( //Projectile entity has a transform component.
						parentEntityPosY + (parentEntityHeight / 2),
						parentEntityPosX + (parentEntityWidth / 2),
						0,
						0,
						projectileHeight,
						projectileWidth,
						1
						);
					projectile.AddComponent<SpriteComponent>(textureAssetID); //Projectile entity has a Sprite component.
					projectile.AddComponent<ProjectileComponent>( //Projectile entity has a Pojectile component.
						projectileSpeed,
						projectileAngle,
						projectileRange,
						projectileLoop
						);
					projectile.AddComponent<ColliderComponent>(//Projectile entity has a Collider component.
						"PROJECTILE",
						parentEntityPosX,
						parentEntityPosY,
						projectileWidth,
						projectileHeight
						);
				}
				//Add collider component
				sol::optional<sol::table> existsAudioComponent = entity["components"]["audio"];
				if (existsAudioComponent != sol::nullopt)
				{
					std::string musicID = entity["components"]["audio"]["musicID"];
					newEntity.AddComponent<AudioComponent>(musicID);
				}
			}
			entityIndex++;
		}
		player = manager.GetEntityByName("player");
	}
	else {
		std::cout << "INVALID SCRIPT" << std::endl;
	}
}

void Engine::HandleCamera() {

	if (player)
	{
		TransformComponent* playerTransform = player->GetComponent<TransformComponent>();
		camera.x = playerTransform->position.x - (WINDOW_WIDTH / 2);
		camera.y = playerTransform->position.y - (WINDOW_HEIGHT / 2);

		camera.x = camera.x < 0 ? 0 : camera.x;
		camera.y = camera.y < 0 ? 0 : camera.y;
		camera.x = camera.x > camera.w ? camera.w : camera.x; //Clamping the values of the camera to the tile map
		camera.y = camera.y > camera.h ? camera.h : camera.y;
	}
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

std::string Engine::CheckValidLua(std::string fileName)
{
	sol::state lua;
	sol::load_result lr = lua.load_file(fileName);


	if (!lr.valid()) { // This checks the syntax of your script, but does not execute it
		sol::error err = lr;
		std::string what = err.what();
		std::cout << "call failed, sol::error::what() is " << what << std::endl;
		return "FAIL";
	}
	else
	{
		sol::protected_function_result result1 = lr(); // this causes the script to execute
		if (!result1.valid()) {
			sol::error err = result1;
			std::string what = err.what();
			std::cout << "call failed, sol::error::what() is " << what << std::endl;
			return "FAIL";
		}
		else
			std::cout << "VALID SCRIPT" << std::endl;
		return "PASS";
	}
}

void Engine::Update()
{	/*
	* Loop is used to allow the program to wait until ~16ms has ellapsed since last frame.
	* This is important check on faster hardware, as it could of updated the game in less than ~16ms.
	*/
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
	/* 
	* This funtion clears the back buffer, it then draws all the game objects.
	* Finally it swaps the front and back buffer. This is called Double Buffering
	*/

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
	Mix_Quit();
	SDL_Quit();
}