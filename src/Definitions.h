#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <SDL.h>

const unsigned int WINDOW_WIDTH = 800; //These are just default values for the camera.
const unsigned int WINDOW_HEIGHT = 600;
const unsigned int FPS_TARGET = 60;
const unsigned int FRAME_TIME_TARGET = 1000 / FPS_TARGET; //FRAME_TIME_TARGET should = ~16ms
enum LayerType
{
	TILEMAP_LAYER = 0,
	VEGETATION_LAYER = 1,
	ENEMY_LAYER = 2,
	PLAYER_LAYER = 3,
	PROJECTILE_LAYER = 4,
	UI_LAYER = 5
};
enum CollisionType
{
	NO_COLLISION,
	PLAYER_ENEMY_COLLISION,
	PLAYER_PROJECTILE_COLLISION,
	ENEMY_PROJECTILE_COLLISION,
	PLAYER_VEGETATION_COLLIDER,
	PLAYER_LEVEL_COMPLETE_COLLISION

};
const unsigned int NUM_LAYERS = 6;
const SDL_Color WHITE_COLOUR = { 255,255,255,255 }; //r,g,b,transparancy
const SDL_Color GREEN_COLOUR = { 0,255,0,255 };
#endif
