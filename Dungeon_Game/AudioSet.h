#pragma once

#include "Basis.h"

class AudioSet
{
private:
	Mix_Chunk* Gunshot;
	Mix_Chunk* Reload;
	Mix_Chunk* Gate;
	Mix_Music* Ambience;

public:
	AudioSet();
	~AudioSet();
	void PlayGunShot();
	void PlayReload();
	void PlayGate();
	void PlayAmbience();
};