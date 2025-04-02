#pragma once

#include "Turrets.h"

class TurretManager
{
public:
	vector<Turret_Wall> Turret_Wall_location;
	vector<Turret_Laser> Turret_Laser_location;

public:
	void RunTurrets(SDL_Renderer* renderer, const SDL_Rect& camera, vector<vector<int>>& ColliderMap, SDL_Texture* laserImg, const float& delta, Player& player);

	void Store_Turret_Wall_Location(const vector<vector<int>>& ColliderMap);
	void Turret_Connect(const SDL_Rect& camera, vector<vector<int>>& ColliderMap);

	void Store_Turret_Laser_Location(const vector<vector<int>>& ColliderMap);
	void All_Turret_Shoot(SDL_Renderer* renderer, const SDL_Rect& camera, vector<vector<int>>& ColliderMap, SDL_Texture* laserImg, const float& delta, Player& player);
};