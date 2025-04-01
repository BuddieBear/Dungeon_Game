#pragma once

#include "basis.h"
#include "Character.h"

class InGameUI
{
private:
	//player bar Texture
	TTF_Font* font;
	SDL_Texture* PlayerBarBackground;
	SDL_Texture* PlayerHp;
	vector<SDL_Texture*> RevolverAmmo;

	//Rect:
	SDL_Rect PlayerBarRect, PlayerHPRect,  RevolverRect;
	SDL_Rect PlayerHP_NumRect, Ammo_NumRect;


public:
	void Init(SDL_Renderer* renderer);
	void RenderPlayerBar(SDL_Renderer* renderer, Player& player);
	//maybe minimap
};