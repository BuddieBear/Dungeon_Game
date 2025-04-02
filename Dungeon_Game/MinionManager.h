#pragma once

#include "Minion.h"

class Melee_Minion;

class MinionManager
{
private:
	vector<Melee_Minion> Melee_Location;
	SDL_Texture* Melee;
public:
	~MinionManager();
	void GetMelee_Minion(vector<vector<int>>& ColliderMap, SDL_Texture* Melee_Text, const SDL_Rect& camera);
	void Run_Melee_Minion(SDL_Renderer* renderer, const SDL_Rect& camera, Player& player, vector<vector<int>>& ColliderMap, const float& delta);
};