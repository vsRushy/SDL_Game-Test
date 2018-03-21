#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"

#define MAX_MUSIC 50

struct Mix_Music;

class ModuleAudio : public Module {

public:
	
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	Mix_Music* const LoadMusic(const char* path);

public:

	Mix_Music* music[MAX_MUSIC] = { nullptr };
};

#endif // __ModuleAudio_H__