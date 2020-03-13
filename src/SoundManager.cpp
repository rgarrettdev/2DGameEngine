#include "SoundManager.h"

Mix_Music* SoundManager::LoadMusic(const char* fileName)
{
	return Mix_LoadMUS(fileName);
}

Mix_Chunk* SoundManager::LoadSound(const char* fileName)
{
	return Mix_LoadWAV(fileName);
}

void SoundManager::Play(Mix_Music *music, int loops)
{
	Mix_PlayMusic(music, loops);
}
