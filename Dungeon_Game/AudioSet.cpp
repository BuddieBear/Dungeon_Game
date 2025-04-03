#include "AudioSet.h"

AudioSet::AudioSet()
{
	this->Gunshot = Mix_LoadWAV("Sounds/GunShot.wav");
	this->Reload = Mix_LoadWAV("Sounds/Reload.wav");
	this->Gate = Mix_LoadWAV("Sounds/Gate.wav");
	this->Button = Mix_LoadWAV("Sounds/Button.wav");

	Mix_VolumeChunk(Gunshot, 64);

	this->Ambience = Mix_LoadMUS("Sounds/Ambience.mp3");

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "SDL_mixer could not initialize! Error: " << Mix_GetError() << std::endl;
		return;
	}
}
AudioSet::~AudioSet()
{
	Mix_FreeChunk(Gunshot);
	Mix_FreeChunk(Reload);
	Mix_FreeChunk(Gate);
	Mix_FreeChunk(Button);

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
void AudioSet::PlayButton() 
{
	if (Button) 
	{
		Mix_PlayChannel(-1, Button, 0);
	}
	else 
	{
		std::cerr << "Button sound not loaded!" <<  std::endl;
	}
}

void AudioSet::PlayAmbience()
{
	Mix_PlayMusic(Ambience, -1);
}