#pragma once

#include "basis.h"
#include "SDL_Utils.h"
#include "Character.h"

class ghost
{
private:
	int x, y; //Map location
	int speed = 100;
	int x_speed, y_speed;
	float angle;
	bool alive = true;

	int GhostSize = 48;
	SDL_Texture* GhostImg;
	SDL_Rect GhostHitbox;

public:
	void ghostInit(int x0, int y0, SDL_Texture* TextGhost, SDL_Rect camera);
	void RunGhost(SDL_Renderer* renderer, SDL_Rect camera, Player& player, float delta);
	void Move(SDL_Renderer* renderer, SDL_Rect player, SDL_Rect camera, float delta);
	bool HitPlayer(SDL_Rect player, SDL_Rect camera);
	void Render(SDL_Renderer* renderer, SDL_Rect camera);
};