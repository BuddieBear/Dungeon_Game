#pragma once

#include "Basis.h"
#include "Character.h"
#include "MinionManager.h"

class MinionManager;

class Melee_Minion
{
private:
	int x, y ; //Map location
	int speed = 5;
	int x_speed = 0, y_speed = 0;
	float angle = 0;


	int MinionSize = 48;
	Uint32 lastUpdateTime = 0;
	SDL_Rect Hitbox;

public:
	bool alive = true;
	friend class MinionManager;

	void Init(int startX, int startY, const SDL_Rect& camera);
	void Run(SDL_Renderer* renderer, const SDL_Rect& camera, Player& player, SDL_Texture* Minion_Text, vector<vector<int>>& ColliderMap, const float& delta); // run the minion
	void Move(SDL_Renderer* renderer, const SDL_Rect& player, const SDL_Rect& camera, vector <vector<int>>& ColliderMap, const float& delta);
	bool HitPlayer(Player& player, const SDL_Rect& camera);
	void Render(SDL_Renderer* renderer, SDL_Texture* Text, const SDL_Rect& camera);
};