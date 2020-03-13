#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "./Engine.h"

class SoundManager
{
public:
	static Mix_Music* LoadMusic(const char* fileName);
	static Mix_Chunk* LoadSound(const char* fileName);

	static void Play(Mix_Music* music, int loops);

private:

};

#endif // !SOUNDMANAGER_H