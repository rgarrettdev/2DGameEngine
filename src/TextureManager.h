#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "./Engine.h"

class TextureManager
{
public:
	//since SDL is a C API, pass const char*.
	static SDL_Texture* LoadTexture(const char* fileName); 

	//Pass SDL texture pointer, source rectangle and destination rectangle and if the texture needs flipping.
	static void Draw(SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect destinationRect, SDL_RendererFlip flip);

private:

};


#endif
