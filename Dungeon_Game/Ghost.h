#pragma once

#include "basis.h"
#include "SDL_Utils.h"
#include "Character.h"

class ghost
{
private:
	int x = start_1_x + 400, y = start_1_y + 600 ; //Map location
	int speed = 3;
	int x_speed =0, y_speed =0;
	float angle =0;
	

	int GhostSize = 48;
	SDL_Texture* GhostImg = nullptr;
	SDL_Rect GhostHitbox;

public:
	bool alive = true;

	void ghostInit(SDL_Texture* TextGhost, SDL_Rect camera);
	void RunGhost(SDL_Renderer* renderer, SDL_Rect camera, Player& player, float delta);
	void Move(SDL_Renderer* renderer, SDL_Rect player, SDL_Rect camera, float delta);
	bool HitPlayer(SDL_Rect player, SDL_Rect camera);
	void Render(SDL_Renderer* renderer, SDL_Rect camera);
};