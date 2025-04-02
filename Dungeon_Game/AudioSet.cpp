#include "AudioSet.h"

AudioSet::AudioSet()
{
	this->Gunshot = Mix_LoadWAV("Sounds/GunShot.wav");
	this->Reload = Mix_LoadWAV("Sounds/Reload.wav");
	this->Gate = Mix_LoadWAV("Sounds/Gate.wav");
	Mix_VolumeChunk(Gunshot, 64);

	this->Ambience = Mix_LoadMUS("Sounds/Ambience.mp3");

}
AudioSet::~AudioSet()
{
	Mix_FreeChunk(Gunshot);
	Mix_FreeChunk(Reload);
	Mix_FreeChunk(Gate);

	Mix_FreeMusic(Ambience);
	Mix_CloseAudio();
}
void AudioSet::PlayGunShot()
{
	Mix_PlayChannel(-1, Gunshot, 0);
}
void AudioSet::PlayReload()
{
	Mix_PlayChannel(-1, Reload, 0);
}
void AudioSet::PlayGate()
{
	Mix_PlayChannel(-1, Gate, 0);
}

void AudioSet::PlayAmbience()
{
	Mix_PlayMusic(Ambience, -1);
}