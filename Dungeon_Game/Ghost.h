#pragma once

#include "basis.h"
#include "SDL_Utils.h"
#include "Character.h"

class ghost
{
private:
	int x,y ; //Map location
	int speed = 3;
	int x_speed =0, y_speed =0;
	float angle =0;
	

	int GhostSize = 48;
	SDL_Texture* GhostImg = nullptr;
	SDL_Rect GhostHitbox;

public:
	bool alive = true;

	void ghostInit(int x0,  int y0, SDL_Texture* TextGhost, const SDL_Rect& camera);
	void RunGhost(SDL_Renderer* renderer,const SDL_Rect& camera, Player& player, const float& delta);
	void Move(SDL_Renderer* renderer, const SDL_Rect& player, const SDL_Rect& camera, const float& delta);
	bool HitPlayer(const SDL_Rect& player, const SDL_Rect& camera);
	void Render(SDL_Renderer* renderer, const SDL_Rect& camera);
};