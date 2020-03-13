#ifndef AUDIOCOMPONENT_H
#define AUDIOCOMPONENT_H

#include "../EntityManager.h"
#include "../AssetManager.h"
#include <SDL_mixer.h>

class AudioComponent : public Component
{
public:
	AudioComponent(std::string musicID) {
		this->bgm = Engine::assetManager->GetMusic(musicID);
		this->effect = NULL;
	}
	~AudioComponent(){
		Mix_FreeMusic(bgm);
	}

	void Initialise() override {
		SoundManager::Play(bgm, -1); //-1 is infintity
	}

private:
	Mix_Music *bgm; //Longer sound files
	Mix_Chunk *effect; //Short sound files
};

#endif // !AUDIOCOMPONENT_H

