#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"
#include "SDL_Mixer/include/SDL_mixer.h"

#pragma comment(lib, "SDL_Mixer/libx86/SDL2_mixer.lib")

ModuleAudio::ModuleAudio() : Module() {}

ModuleAudio::~ModuleAudio() {}

bool ModuleAudio::Init() {

	LOG("Init SDL Audio system");
	bool ret = true;

	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}

	music[0] = App->audios->LoadMusic("Assets/Audio/04_Stage_1 -The Moon-Loop.ogg");

	return ret;
}

bool ModuleAudio::CleanUp() {

	LOG("Freeing music and Mixer library");

	for (int i = 0; i < MAX_MUSIC; i++) {

		if (music[i] != nullptr)

			Mix_FreeMusic(music[i]);
	}

	Mix_CloseAudio();
	Mix_Quit();

	return true;
}

Mix_Music* const ModuleAudio::LoadMusic(const char* path) {

	Mix_Music* loadMusic = Mix_LoadMUS(path);
	if (!music) {

		LOG("Music cannot be loaded: %s", Mix_GetError());
		return nullptr;
	}

	for (int i = 0; i < MAX_MUSIC; i++) {
		
		if (music[i] == nullptr) {
			
			music[i] = loadMusic;
			if (!music[i]) {

				LOG("Music cannot be loaded: %s\n", Mix_GetError());
				return nullptr;
			}

			return music[i];
		}

		Mix_FreeMusic(loadMusic);
	}

	return nullptr;
}
