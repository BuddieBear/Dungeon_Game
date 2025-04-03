#pragma once

#include "Basis.h"

class AudioSet
{
private:
	Mix_Chunk* Gunshot;
	Mix_Chunk* Reload;
	Mix_Chunk* Gate;
	Mix_Chunk* Button;
	Mix_Music* Ambience;

public:
	AudioSet();
	~AudioSet();
	void PlayGunShot();
	void PlayReload();
	void PlayGate();
	void PlayButton();
	void PlayAmbience();
};